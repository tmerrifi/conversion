
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/path.h>
#include <linux/string.h>
#include <linux/rmap.h>
#include <linux/highmem.h>
#include <linux/pagemap.h>
#include <linux/list.h>
#include <linux/swap.h>
#include <linux/poison.h>
#include <linux/random.h>
#include <asm/pgtable.h>
#include <asm/insn.h>
#include <asm/tlbflush.h>

#include "conversion.h"
#include "libudis86/extern.h"
#include "cv_decode.h"
#include "ksnap_writer.h"

int cv_logging_diff_64(uint8_t * local, struct page * ref_page){
  uint8_t * ref;
  int i=0;
  int j=0;
  int total=0;
  
  if (ref_page!=NULL){
      ref = kmap_atomic(ref_page, KM_USER1);
  }
  else{
      return 0;
  }

  if (!ref){
      printk(KSNAP_LOG_LEVEL "failed to map ref %p\n", ref);
      BUG();
  }

  //now do the diff
  for (;i<(PAGE_SIZE/sizeof(uint64_t));++i,j+=sizeof(uint64_t)){
      if (((uint64_t *)local)[i]!=((uint64_t *)ref)[i]){
          total++;
      }
  }
  
  if (ref_page){
    kunmap_atomic(ref, KM_USER1);
  }
  return total;
}

uint8_t * cv_logging_allocate_data_entry(int data_len){
    if (data_len==PAGE_SIZE){
        return (uint8_t *)kmalloc(PAGE_SIZE, GFP_KERNEL);
    }
    else{
        return (uint8_t *)kmem_cache_alloc(cv_seg->logging_data_entry_mem_cache, GFP_KERNEL);
    }
}

void cv_logging_print_stats(struct ksnap * cv_seg){
    int i=0;

    printk(KERN_EMERG "****LOGGING STATS*****");
    printk(KERN_EMERG "pages: %d\n", atomic_read(&cv_seg->logging_pages_count));
    printk(KERN_EMERG "**************************");
    /*    printk(KERN_EMERG "******Opcode stats**********");

    for (;i<256;i++){
        if (cv_seg->logging_stats_opcode[i] > 0){
            printk(KERN_EMERG "one byte opcode %x %d\n", i, cv_seg->logging_stats_opcode[i]);
        }
        if (cv_seg->logging_stats_opcode_two[i] > 0){
            printk(KERN_EMERG "two byte opcode %x %d\n", i, cv_seg->logging_stats_opcode_two[i]);
        }
    }
        
    printk(KERN_EMERG "**************************");*/
}

int cv_logging_page_status_insert(struct ksnap_user_data * cv_user,struct cv_logging_page_status_entry * entry, unsigned long index){
    if (radix_tree_insert(&cv_user->logging_page_status, index, entry)==-EEXIST){
        return -1;
    }
    else{
        return 0;
    }
}

 struct cv_logging_page_status_entry * cv_logging_page_status_lookup(struct ksnap_user_data * cv_user, unsigned long index){
    return radix_tree_lookup(&cv_user->logging_page_status, index);
}

struct cv_logging_page_status_entry * cv_logging_page_status_entry_init(pte_t * pte, unsigned long pfn){
    struct cv_logging_page_status_entry * entry = kmalloc(sizeof(struct cv_logging_page_status_entry), GFP_KERNEL);
    entry->pte=pte;
    entry->pfn=pfn;
    return entry;
}

unsigned long cv_logging_get_index(unsigned long addr, unsigned long page_index, int is_page_level){
    //lower 7 bits reserved for cache line index
    //LSB reserved for marking it as page level

    unsigned long result = page_index << 7UL;
    if (is_page_level){
        result|=1UL;
    }
    else{
        result|=(((addr & ~PAGE_MASK)/CV_LOGGING_LOG_SIZE)<<1UL);
    }
    return result;
}

void cv_merge_line(uint8_t * local, uint8_t * ref, uint8_t * latest){
    cv_three_way_merge(local, ref, latest, CV_LOGGING_LOG_SIZE/sizeof(uint64_t) );
}

void cv_logging_cow_page_fault(struct vm_area_struct * vma, struct cv_logging_entry * logging_entry,
                               unsigned long faulting_addr, pte_t * pte){
    pte_t page_table_e;
    
    logging_entry->data=cv_logging_allocate_data_entry(PAGE_SIZE);
    logging_entry->addr=(faulting_addr & PAGE_MASK);
    logging_entry->data_len=PAGE_SIZE;
    logging_entry->line_index=0;
    cv_logging_set_dirty(logging_entry);
    
    //now do the copy
    memcpy(logging_entry->data, (uint8_t *)logging_entry->addr, PAGE_SIZE);
    printk(KERN_EMERG "about to set PTE entry %lu %lu for page\n", page_table_e, *pte); 
    //now fix the pte and make it writeable
    //get the pre-existing pte value and clear the pte pointer
    page_table_e = ptep_get_and_clear(vma->vm_mm, (uint8_t *)logging_entry->addr, pte);
    //make writeable and set it back
    set_pte(pte, pte_mkwrite(page_table_e));
    __flush_tlb_one(logging_entry->addr);
    printk(KERN_EMERG "set PTE entry %lx %lx for page\n", page_table_e, *pte); 
}

int cv_logging_fault(struct vm_area_struct * vma, struct ksnap * cv_seg, struct ksnap_user_data * cv_user,
                      struct pt_regs * regs, unsigned long faulting_addr){
    //get the page index
    struct snapshot_pte_list * dirty_list_entry;
    uint32_t page_index = (faulting_addr - vma->vm_start)/PAGE_SIZE;
    struct cv_logging_page_status_entry * logging_status_entry = cv_logging_page_status_lookup(cv_user, page_index);
    printk(KERN_EMERG "logging fault, pid: %d, page index: %d, data %d\n",
           current->pid, page_index, *((int *)faulting_addr));
    
    if (logging_status_entry){
        //we've got a local logging entry, so we can proceed from here...
        /*create the new pte entry*/
        dirty_list_entry = kmem_cache_alloc(cv_seg->pte_list_mem_cache, GFP_KERNEL);
        dirty_list_entry->type=CV_DIRTY_LIST_ENTRY_TYPE_LOGGING;
        dirty_list_entry->page_index = page_index;
        dirty_list_entry->obsolete_version=~(0x0);
        dirty_list_entry->mm = current->mm;
        dirty_list_entry->checkpoint = 0;
        dirty_list_entry->wait_revision = 0;
        //just adding this to the lookup so if we find it later we can throw BUG();
        conv_add_dirty_page_to_lookup(vma,dirty_list_entry, page_index);
        INIT_LIST_HEAD(&dirty_list_entry->list);
        /*now we need to add the pte to the list */
        list_add_tail(&dirty_list_entry->list, &cv_user->dirty_pages_list->list);
        if (!cv_decode_try_and_execute_write()){
            printk(KERN_EMERG "logging fault CoW, pid: %d, page index: %d\n",
                   current->pid, page_index);
            //fallback and cow the page
            cv_logging_cow_page_fault(vma, cv_list_entry_get_logging_entry(dirty_list_entry), faulting_addr, logging_status_entry->pte);
            printk(KERN_EMERG "DONE logging fault CoW, pid: %d, page index: %d\n",
                   current->pid, page_index);
        }

        cv_meta_inc_dirty_page_count(vma);
        cv_user->dirty_pages_list_count++;
        
        return 1;
    }
    else{
        return 0;
    }
}

void cv_logging_entry_lookup(struct ksnap * cv_seg){
    
}


/*void cv_logging_instruction_stats(struct ksnap * cv_seg, struct ksnap_user_data * cv_user, unsigned long addr){
    struct ud dis;
    ud_init(&dis);
    ud_set_mode(&dis,64);
    ud_set_vendor(&dis,UD_VENDOR_INTEL);
    ud_set_input_buffer(&dis, (uint8_t *)addr, 16);
    ud_set_syntax(&dis,UD_SYN_INTEL);
    int len = ud_disassemble(&dis);
    int randnum;
    get_random_bytes(&randnum,sizeof(int));
    
    if (len > 0 && randnum % 1024 == 0){
        printk(KERN_INFO "ins: %s\n", ud_insn_asm(&dis));
        //printk(KERN_INFO "ins: %s\n", ud_lookup_mnemonic(ud_insn_mnemonic(&dis)));
    }
    }*/


/*void cv_logging_instruction_stats(struct ksnap * cv_seg, struct ksnap_user_data * cv_user, unsigned long addr){
    struct insn instruction;
    insn_init(&instruction, (void *)addr, 1);
    insn_get_opcode(&instruction);
    if (instruction.opcode.nbytes > 0){
        spin_lock(&cv_seg->lock);
        if (instruction.opcode.nbytes==1){
            cv_seg->logging_stats_opcode[instruction.opcode.bytes[0] % 256]++;
        }
        else if (instruction.opcode.nbytes==2 && instruction.opcode.bytes[0]==0x0f){
            cv_seg->logging_stats_opcode_two[instruction.opcode.bytes[1] % 256]++;
        }
        else{
            cv_seg->logging_stats_opcode[0xd6]++;
        }
        spin_unlock(&cv_seg->lock);
    }
    
    //opcode->bytes[0]
    //opcode->nbytes = 1;
    }*/
