
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
#include "cv_store_interpreter_functions.h"

int cv_logging_diff_64(uint8_t * local, struct page * ref_page){
  uint8_t * ref;
  int i=0;
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
  for (;i<(PAGE_SIZE/sizeof(uint64_t));i+=sizeof(uint64_t)){
      if (((uint64_t *)local)[i]!=((uint64_t *)ref)[i]){
          total++;
      }
  }
  
  if (ref_page){
    kunmap_atomic(ref, KM_USER1);
  }
  return total;
}

uint8_t * cv_logging_allocate_data_entry(int data_len, struct ksnap * cv_seg){
    if (data_len==PAGE_SIZE){
        return (uint8_t *)kmalloc(PAGE_SIZE, GFP_KERNEL);
    }
    else{
        return (uint8_t *)kmem_cache_alloc(cv_seg->logging_data_entry_mem_cache, GFP_KERNEL);
    }
}

void cv_logging_free_data_entry(int data_len, struct ksnap * cv_seg, void * data){
    if (data==NULL){
        return;
    }
    else if (data_len==PAGE_SIZE){
        conv_debug_memory_free(data);
        kfree(data);
    }    
    else{
        conv_debug_memory_free(data);
        kmem_cache_free(cv_seg->logging_data_entry_mem_cache, data);
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

struct cv_logging_page_status_entry * cv_logging_page_status_entry_init(pte_t * pte, unsigned long pfn,
                                                                        unsigned long page_index, uint64_t version_num){
    struct cv_logging_page_status_entry * entry = kmalloc(sizeof(struct cv_logging_page_status_entry), GFP_KERNEL);
    conv_debug_memory_alloc(entry);
    entry->pte=pte;
    entry->pfn=pfn;
    entry->logging_writes=0;
    entry->entries_allocated=0;
    entry->wait_entry=NULL;
    memset(entry->lines, 0, (PAGE_SIZE/CV_LOGGING_LOG_SIZE) * sizeof(struct snapshot_pte_list *));
    entry->page_entry=NULL;
    entry->page_index=page_index;
    entry->cow_version=version_num;
    return entry;
}

unsigned long cv_logging_get_index(unsigned long page_index, unsigned long line_index, int is_page_level){
    //lower 7 bits reserved for cache line index
    //LSB reserved for marking it as page level

    unsigned long result = page_index << 7UL;
    if (is_page_level){
        result|=1UL;
    }
    else{
        result|=((line_index)<<1UL);
    }
    return result;
}

void cv_merge_line(uint8_t * local, uint8_t * ref, uint8_t * latest){
    cv_three_way_merge(local, ref, latest, CV_LOGGING_LOG_SIZE/sizeof(uint64_t) );
}

//this funtion does not flush the tlb!!!
struct page * cv_logging_cow_page(struct vm_area_struct * vma, pte_t * pte, unsigned long faulting_addr){
    struct page * new_page, * old_page;
    pte_t new_pte_entry;
    uint8_t * kaddr;
    unsigned long page_addr=faulting_addr & PAGE_MASK;
    
    //get the old page
    old_page = pte_page(*pte);
    //allocate a new page
    new_page = alloc_page_vma(GFP_HIGHUSER_MOVABLE, vma, page_addr);
    conv_debug_memory_alloc(new_page);
    __SetPageUptodate(new_page);
    //add it to rmap
    page_add_new_anon_rmap(new_page, vma, page_addr);
    /* //do the copy */
    kaddr = (uint8_t *)kmap_atomic(new_page, KM_USER0);
    memcpy(kaddr,(uint8_t *)page_addr,PAGE_SIZE);
    kunmap_atomic(kaddr, KM_USER0);
    //updating the pte with the new PFN and flush the TLB
    new_pte_entry = mk_pte(new_page, vma->vm_page_prot);
    set_pte(pte, new_pte_entry);
    //deal with the old page
    page_remove_rmap(old_page);
    put_page(old_page);
#ifdef CONV_LOGGING_ON
    printk(KERN_EMERG "cv_logging: CoW'd oldpage: %p, newpage: %p, pid: %d\n",
           old_page, new_page, current->pid);
#endif
    //return the new pfn
    
    return new_page;
}

void cv_logging_cow_page_fault(struct vm_area_struct * vma,
                               struct snapshot_pte_list * entry,
                               struct cv_logging_entry * logging_entry,
                               struct cv_logging_page_status_entry * logging_status_entry,
                               unsigned long faulting_addr, pte_t * pte, int force_cow_page){
    pte_t page_table_e;
    int i=0;

    struct ksnap * cv_seg=ksnap_vma_to_ksnap(vma);
    struct ksnap_user_data * cv_user=ksnap_vma_to_userdata(vma);

    if (force_cow_page){
        struct page * new_page = cv_logging_cow_page(vma, pte, faulting_addr);
        logging_status_entry->pfn=page_to_pfn(new_page);
        logging_status_entry->cow_version=cv_user->version_num;
    }
    
    if (cv_logging_is_full_page(logging_entry) && conv_is_checkpointed_logging_entry(logging_entry)){
        //this is a special case, because the rest of this function assumes we are
        //transitioning from a logging entry to a page level entry. If this is a checkpointed
        //page then we don't have much work to do
        memcpy(logging_entry->data, (uint8_t *)cv_logging_line_start(faulting_addr), PAGE_SIZE);
        //need to set the dirty bit
        cv_logging_set_dirty(logging_entry);
        goto write_protect;
    }

    //unless its been checkpointed, there's no reason this should happen
    BUG_ON(cv_logging_is_full_page(logging_entry));
    
    //remove from the lookup too
    conv_dirty_delete_lookup(cv_user, entry->page_index,
                             logging_entry->line_index, 0);

    //allocate new objects for holding PAGE_SIZE data
    uint8_t * new_data=cv_logging_allocate_data_entry(PAGE_SIZE, cv_seg);
    conv_debug_memory_alloc(new_data);
    //set the logging status page entry
    logging_status_entry->page_entry=entry;
    //now do the copy of the ENTIRE page
    memcpy(new_data, (uint8_t *)(faulting_addr & PAGE_MASK), PAGE_SIZE);

    //its possible that the logging_entry is NULL if we've exceeded the number of writes we can perform for
    //a page but this is the first attempted write for this cache line
    if (logging_entry->data!=NULL){
        //we reuse this entry, so we need to copy over our old data
        memcpy(new_data + CV_LOGGING_LOG_SIZE * logging_entry->line_index, logging_entry->data, CV_LOGGING_LOG_SIZE);
        CV_LOGGING_DEBUG_PRINT_LINE(((uint8_t *)(new_data + CV_LOGGING_LOG_SIZE * logging_entry->line_index)),
                                    entry->page_index,
                                    logging_entry->line_index,
                                    "cv_logging: copy old");
        //free the old data
        cv_logging_free_data_entry(CV_LOGGING_LOG_SIZE, cv_seg, logging_entry->data);
    }
    
    //point to the new data
    logging_entry->data=new_data;
    
    //is there checkpoint data to deal with????
    if (conv_is_checkpointed_logging_entry(logging_entry)){
        uint8_t * new_checkpoint_data=cv_logging_allocate_data_entry(PAGE_SIZE, cv_seg);
        conv_debug_memory_alloc(new_checkpoint_data);
        //start with the current page
        memcpy(new_checkpoint_data, new_data, PAGE_SIZE);
        memcpy(new_checkpoint_data + CV_LOGGING_LOG_SIZE * logging_entry->line_index, logging_entry->data, CV_LOGGING_LOG_SIZE);
        //printk(KERN_EMERG "old checkpoint data .... %p\n", logging_entry->local_checkpoint_data);
        //free the old checkpoint data
        cv_logging_free_data_entry(CV_LOGGING_LOG_SIZE, cv_seg, logging_entry->local_checkpoint_data);
        //now set the logging entry
        logging_entry->local_checkpoint_data=new_checkpoint_data;
    }

    //clear the line we just sorted out, so we don't see it again when we walk all the dirty lines
    logging_status_entry->lines[logging_entry->line_index]=0;
    
    /*** now its safe to setup new properties*****/
    logging_entry->data_len=PAGE_SIZE;
    logging_entry->line_index=0;
    logging_entry->addr=(faulting_addr & PAGE_MASK);        
    cv_logging_set_dirty(logging_entry);
    /*********done setting properties**********/        
            
    //now we need to walk through each line, copy data and free resources
    for(;i<(PAGE_SIZE/CV_LOGGING_LOG_SIZE);i++){
        if (logging_status_entry->lines[i]){
            struct snapshot_pte_list * entry_old = logging_status_entry->lines[i];
            /* printk(KERN_EMERG "copying the old stuff, pid: %d, page: %d, i: %d, entry: %p, entry_old %p\n", */
            /*        current->pid, entry->page_index, i, entry, entry_old); */

            struct cv_logging_entry * logging_entry_old = cv_list_entry_get_logging_entry(entry_old);
            /* printk(KERN_EMERG "copying the old stuff, pid: %d, page: %d, line: %d, i: %d, entry: %p, entry_old %p\n", */
            /*        current->pid, entry->page_index, logging_entry_old->line_index, i, entry, entry_old); */
            //copy the reference data over
            memcpy(logging_entry->data + i*CV_LOGGING_LOG_SIZE, logging_entry_old->data, CV_LOGGING_LOG_SIZE);
            CV_LOGGING_DEBUG_PRINT_LINE(((uint8_t *)logging_entry_old->data),
                                        entry->page_index,
                                        logging_entry->line_index,
                                        "cv_logging : copy over ref");
            //if there's checkpoint data, we need that too
            if (conv_is_checkpointed_logging_entry(logging_entry_old)){
                //its possible that we haven't actually allocated space to store the local checkpoint data for the page
                //level entry. Lets do that now
                if (logging_entry->local_checkpoint_data==NULL){
                    logging_entry->local_checkpoint_data=cv_logging_allocate_data_entry(PAGE_SIZE, cv_seg);
                    conv_debug_memory_alloc(logging_entry->local_checkpoint_data);
                    //copy over what's in logging_entry->data...this will include anything we missed, for example logging
                    //entries that weren't checkpointed (but others were).
                    memcpy(logging_entry->local_checkpoint_data, logging_entry->data, PAGE_SIZE);
                }
                memcpy(logging_entry->local_checkpoint_data + i*CV_LOGGING_LOG_SIZE, logging_entry_old->local_checkpoint_data, CV_LOGGING_LOG_SIZE);
                //free the checkpoint data
                cv_logging_free_data_entry(logging_entry_old->data_len, cv_seg, logging_entry_old->local_checkpoint_data);
            }
            else if (conv_is_checkpointed_logging_entry(logging_entry)){
                //its possible that some logging entries weren't checkpointed and others were. So here, we need to copy our
                //reference data into local_checkpoint_data
                memcpy(logging_entry->local_checkpoint_data + i*CV_LOGGING_LOG_SIZE, logging_entry_old->data, CV_LOGGING_LOG_SIZE);
            }            
            //remove from dirty list
            list_del(&entry_old->list);
            //remove from dirty list lookup
            conv_dirty_delete_lookup(cv_user, entry_old->page_index,logging_entry_old->line_index,0);
            //free the old data
            cv_logging_free_data_entry(logging_entry_old->data_len, cv_seg, logging_entry_old->data);
            //free the entry
            kmem_cache_free(cv_seg->pte_list_mem_cache, entry_old);
            //clear this entry
            logging_status_entry->lines[i]=NULL;
        }
    }
    //add the new one (page level)
    conv_add_dirty_page_to_lookup(vma, entry, entry->page_index, logging_entry->line_index, 1);
    //add to the dirty list
    //list_add_tail(&entry->list, &cv_user->dirty_pages_list->list);
    
 write_protect:
    
    //now fix the pte and make it writeable
    //get the pre-existing pte value and clear the pte pointer
    page_table_e = ptep_get_and_clear(vma->vm_mm, (uint8_t *)logging_entry->addr, pte);
    //make writeable and set it back
    set_pte(pte, pte_mkwrite(page_table_e));
    __flush_tlb_one(logging_entry->addr);
}

void cv_logging_store_interpreter_fault(unsigned long faulting_addr, struct pt_regs * regs){
    if (!interpret(regs->ip, 15, faulting_addr, regs)){
        //fallback to CoW
    }
}

void cv_logging_line_debug_print(struct snapshot_pte_list * dirty_list_entry,
                                 struct cv_logging_entry * logging_entry,
                                 char * message){
    if (!cv_logging_is_full_page(logging_entry)){
        char str_arr[CV_LOGGING_LOG_SIZE*2*6];
        int i=0;
        int j=0;
        uint8_t * addr = logging_entry->addr;
        //if (conv_debug_logging_is_line(dirty_list_entry->page_index, logging_entry->line_index)){
        for (;i<CV_LOGGING_LOG_SIZE;i++){
            j+=sprintf(str_arr + j, " %d:%x", i, *(addr+i));
        }
        printk(KERN_INFO "DEBUG: %s - pid: %d, page: %d, entry %p, line: %d - data: %s\n",
               message, current->pid, dirty_list_entry->page_index, logging_entry, logging_entry->line_index, str_arr);
        //}
        i=j=0;
        addr = logging_entry->data;
        for (;i<CV_LOGGING_LOG_SIZE;i++){
            j+=sprintf(str_arr + j, " %d:%x", i, *(addr+i));
        }
        printk(KERN_INFO "DEBUG-DATA: %s - pid: %d, page: %d, line: %d - data: %s\n",
               message, current->pid, dirty_list_entry->page_index, logging_entry->line_index, str_arr);

    }
}

int cv_logging_fault(struct vm_area_struct * vma, struct ksnap * cv_seg, struct ksnap_user_data * cv_user,
                      struct pt_regs * regs, unsigned long faulting_addr){
    //get the page index
    struct snapshot_pte_list * dirty_list_entry;
    struct cv_logging_entry * logging_entry;
    uint64_t write_width=0;
    int handled=0;
    uint32_t page_index=(faulting_addr - vma->vm_start)/PAGE_SIZE;
    uint32_t line_index=cv_logging_line_index(faulting_addr);
    int force_cow_page=0;
    
    struct cv_logging_page_status_entry * logging_status_entry = cv_logging_page_status_lookup(cv_user, page_index);
    //printk(KERN_EMERG "logging fault, pid: %d, page index: %d, data %d, addr %p\n",
    //     current->pid, page_index, *((int *)faulting_addr), faulting_addr);
    
    if (!logging_status_entry){
        return 0;
    }

    //we need to check and see if we've forked a new thread lately. If we have, then we can't just
    //modify this "private" page because another thread might be using it as a reference page. So we
    //have to CoW our private page.
    if (logging_status_entry->cow_version < cv_user->forked_version_num){
#ifdef CONV_LOGGING_ON
        printk(KERN_EMERG "cv_logging: forcing a cow, pid: %d, page: %d\n", current->pid, page_index);
#endif
        force_cow_page=1;
    }
    
    //is there already a dirty entry for this line?
    dirty_list_entry=conv_dirty_search_lookup(cv_user, page_index,
                                              cv_logging_line_index(faulting_addr), 0);
    if (!dirty_list_entry){
        //try again at the page level
        dirty_list_entry=conv_dirty_search_lookup(cv_user, page_index,
                                                  0, 1);
    }
    //if no entry exists, need to allocate one
    if (!dirty_list_entry){
        //we've got a local logging entry, so we can proceed from here...
        /*create the new pte entry*/
        dirty_list_entry = kmem_cache_alloc(cv_seg->pte_list_mem_cache, GFP_KERNEL);
        //printk(KERN_EMERG "allocating a new entry....%p\n", dirty_list_entry);
        dirty_list_entry->type=CV_DIRTY_LIST_ENTRY_TYPE_LOGGING;
        dirty_list_entry->page_index = page_index;
        dirty_list_entry->obsolete_version=~(0x0);
        dirty_list_entry->mm = current->mm;
        dirty_list_entry->checkpoint = 0;
        dirty_list_entry->wait_revision = 0;
        logging_entry = cv_list_entry_get_logging_entry(dirty_list_entry);
        logging_entry->addr = (faulting_addr & CV_LOGGING_LOG_MASK);
        logging_entry->data_len = CV_LOGGING_LOG_SIZE;
        logging_entry->line_index = cv_logging_line_index(faulting_addr);
        logging_entry->data = NULL;
        logging_entry->local_checkpoint_data = NULL;
        //just adding this to the lookup so if we find it later we can throw BUG();
        conv_add_dirty_page_to_lookup(vma,dirty_list_entry, page_index, logging_entry->line_index, 0);
        INIT_LIST_HEAD(&dirty_list_entry->list);
        /*now we need to add the pte to the list */
        list_add_tail(&dirty_list_entry->list, &cv_user->dirty_pages_list->list);
        logging_status_entry->entries_allocated++;
    }
    else{
        //just grab the logging entry otherwise
        logging_entry = cv_list_entry_get_logging_entry(dirty_list_entry);
        //printk(KERN_EMERG "CV_LOGGING: entry already exists. pid: %d, cache_line: %d\n", current->pid, logging_entry->line_index);
    }

    //cv_logging_is_full_page will be true if this page was checkpointed
    if (!cv_logging_is_full_page(logging_entry) &&
        logging_status_entry->logging_writes < CV_LOGGING_WRITES_THRESHOLD &&
        !force_cow_page){
        //allocate some space to hold the reference data...but only do it the first time for this entry
        if (logging_entry->data==NULL){
            logging_entry->data = cv_logging_allocate_data_entry(CV_LOGGING_LOG_SIZE, cv_seg);
            conv_debug_memory_alloc(logging_entry->data);            
            memcpy(logging_entry->data,cv_logging_line_start(faulting_addr),CV_LOGGING_LOG_SIZE);
        }
        uint8_t * kaddr_faulting = pfn_to_kaddr(logging_status_entry->pfn) + (faulting_addr & (~PAGE_MASK));
        /* printk(KERN_EMERG "before interpret....\n"); */
        CV_LOGGING_DEBUG_PRINT_LINE( ((uint8_t *) ((size_t)kaddr_faulting & CV_LOGGING_LOG_MASK)),
                                     page_index,
                                     logging_entry->line_index,
                                     "cv_logging: before interpret");
        /* printk(KERN_EMERG "OG data...\n"); */
        CV_LOGGING_DEBUG_PRINT_LINE( ((uint8_t *)logging_entry->data),
                                     page_index,
                                     logging_entry->line_index,                                     
                                     "cv_logging: before interpret refdata");
        
        if ((write_width=interpret(regs->ip, CV_LOGGING_INSTRUCTION_MAX_WIDTH, kaddr_faulting, regs))){
            cv_logging_set_dirty(logging_entry);
            logging_status_entry->logging_writes++;
            handled=1;
            //cv_logging_free_data_entry(CV_LOGGING_LOG_SIZE, cv_seg, logging_entry->data);
            //store this in our logging status entry so we can easily find it later if we switch to page-level
            logging_status_entry->lines[logging_entry->line_index]=dirty_list_entry;
            CV_LOGGING_DEBUG_PRINT_LINE( ((uint8_t *) ((size_t)kaddr_faulting & CV_LOGGING_LOG_MASK)),
                                         page_index,
                                         logging_entry->line_index,
                                         "cv_logging: after interpret");
            
            //we succeeded, figure out if we wrote to more than one cache line
            BUG_ON(cv_logging_line_start(faulting_addr) + write_width > cv_logging_line_start(faulting_addr) + CV_LOGGING_LOG_SIZE);
            //cv_logging_line_debug_print(dirty_list_entry, logging_entry, "added logging entry");
        }
    }
        
    if (!handled){
        /* if (page_index==12){ */
        /*     printk(KERN_EMERG "cow page index: %d, pid: %d, data: %d\n", */
        /*            dirty_list_entry->page_index, current->pid, */
        /*            *((uint8_t *)(logging_entry->addr & PAGE_MASK)) + LOGGING_DEBUG_INDEX ); */
        /* } */
        cv_logging_cow_page_fault(vma, dirty_list_entry, logging_entry,
                                  logging_status_entry, faulting_addr,
                                  logging_status_entry->pte, force_cow_page);
        logging_status_entry->logging_writes=0;
        logging_status_entry->entries_allocated=0;
        
        /* printk(KERN_EMERG "cow page index: %d, pid: %d, data: %d\n", */
        /*        dirty_list_entry->page_index, current->pid, */
        /*        *((uint8_t *)(logging_entry->addr & PAGE_MASK)) + LOGGING_DEBUG_INDEX); */
    }
    cv_meta_inc_dirty_page_count(vma);
    cv_user->dirty_pages_list_count++;
    return 1;
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
