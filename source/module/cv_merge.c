
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
  int i=0;  
  cv_merge_empty_page = kmalloc(PAGE_SIZE, GFP_KERNEL);
  memset(cv_merge_empty_page, 0, PAGE_SIZE);
}

void cv_merge_free(){
  kfree(cv_merge_empty_page);
}

void ksnap_merge(struct page * latest_page, uint8_t * local, struct page * ref_page, struct page * local_page){
  uint8_t * latest, * ref;
  int i=0;

  if (ref_page!=NULL){
    ref = kmap_atomic(ref_page, KM_USER1);
  }
  else{
    ref = cv_merge_empty_page;
  }

  latest = kmap_atomic(latest_page, KM_USER0);

  if (!access_ok(VERIFY_READ, local, PAGE_SIZE)){
      printk(KSNAP_LOG_LEVEL "merge access failed for local %p\n", local);
      BUG();
  }

  if (!ref || !latest){
      printk(KSNAP_LOG_LEVEL "failed to map ref %p or latest %p\n", ref, latest);
      BUG();
  }

  #ifdef CONV_LOGGING_ON
  printk(KSNAP_LOG_LEVEL "pid %d MERGING %lu %p %lu %p\n", current->pid, page_to_pfn(latest_page), local, page_to_pfn(ref_page), ref_page);
  #endif


  //now do the diff
  for (;i<PAGE_SIZE;++i){
    if (unlikely(latest[i]!=ref[i] && local[i]==ref[i])){
        local[i]=latest[i];
    }
  }

  kunmap_atomic(latest, KM_USER0);
  if (ref_page){
    kunmap_atomic(ref, KM_USER1);
  }

}
