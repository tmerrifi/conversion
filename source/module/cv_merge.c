
#include <linux/module.h>	/* Needed by all modules */
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
#include <asm/pgtable.h>
#include <asm/tlbflush.h>
#include <linux/kdebug.h>
#include <linux/notifier.h>
#include <linux/random.h>
#include <linux/spinlock.h>
#include <linux/mman.h>

#include "conversion.h"
#include "cv_merge.h"

uint8_t * cv_merge_empty_page;

void ksnap_merge_init(){
  cv_merge_empty_page = kmalloc(PAGE_SIZE, GFP_KERNEL);
  memset(cv_merge_empty_page, 0, PAGE_SIZE);
}

void cv_merge_free(){
  kfree(cv_merge_empty_page);
}

int cv_three_way_merge(uint8_t * local, uint8_t * ref, uint8_t * latest, int words_to_merge_64bit){
    int i=0;
    int j=0;
    
    int cl_diff=0;

    //now do the diff
    for (;i<words_to_merge_64bit;++i,j+=sizeof(uint64_t)){
        if (((uint64_t *)latest)[i]!=((uint64_t *)ref)[i]){
            //the committed page is different than what our snapshot looked like at the beginning. If we didn't touch this
            //portion of memory, than we can copy the whole thing over.
            if (((uint64_t *)local)[i]==((uint64_t *)ref)[i]){
                ((uint64_t *)local)[i]=((uint64_t *)latest)[i];
            }
            else{
		cl_diff++;
                //otherwise we need to do a more fine-grained comparison
                if (latest[j]!=ref[j] && local[j]==ref[j]){
                    local[j]=latest[j];
                }
                if (latest[j+1]!=ref[j+1] && local[j+1]==ref[j+1]){
                    local[j+1]=latest[j+1];
                }
                if (latest[j+2]!=ref[j+2] && local[j+2]==ref[j+2]){
                    local[j+2]=latest[j+2];
                }
                if (latest[j+3]!=ref[j+3] && local[j+3]==ref[j+3]){
                    local[j+3]=latest[j+3];
                }
                if (latest[j+4]!=ref[j+4] && local[j+4]==ref[j+4]){
                    local[j+4]=latest[j+4];
                }
                if (latest[j+5]!=ref[j+5] && local[j+5]==ref[j+5]){
                    local[j+5]=latest[j+5];
                }
                if (latest[j+6]!=ref[j+6] && local[j+6]==ref[j+6]){
                    local[j+6]=latest[j+6];
                }
                if (latest[j+7]!=ref[j+7] && local[j+7]==ref[j+7]){
                    local[j+7]=latest[j+7];
                }
            }
        }
    }

    return cl_diff;
}

int ksnap_merge(struct page * latest_page, uint8_t * local, struct page * ref_page, struct page * local_page){
  uint8_t * latest, * ref;
  int merged_cachelines;

  if (ref_page!=NULL){
    ref = kmap_atomic(ref_page, KM_USER1);
  }
  else{
    ref = cv_merge_empty_page;
  }

  latest = kmap_atomic(latest_page, KM_USER0);

  if (!ref || !latest){
      printk(KERN_INFO "failed to map ref %p or latest %p\n", ref, latest);
      BUG();
  }

  merged_cachelines = cv_three_way_merge(local, ref, latest, (PAGE_SIZE/sizeof(uint64_t)));
  
  kunmap_atomic(latest, KM_USER0);
  if (ref_page){
    kunmap_atomic(ref, KM_USER1);
  }

  return merged_cachelines;
}


uint8_t * compute_local_addr_for_diff(struct vm_area_struct * vma, unsigned long pfn, unsigned long page_index, int checkpointed){
    uint8_t * local_addr;
    if (checkpointed){
        //we do this because we modify our page and the current version is write-protected
        local_addr=(uint8_t *)pfn_to_kaddr(pfn);
    }
    else{
        local_addr=(uint8_t *)((page_index << PAGE_SHIFT) + vma->vm_start);
    }
    return local_addr;
}

