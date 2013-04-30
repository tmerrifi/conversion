
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

#include "ksnap.h"
#include "cv_merge.h"

unsigned int * cv_merge_empty_page;

void ksnap_merge_init(){
  int i=0;  
  cv_merge_empty_page = kmalloc(PAGE_SIZE, GFP_KERNEL);
  for (;i<(PAGE_SIZE/sizeof(unsigned int));++i){
    cv_merge_empty_page[i]=0;
  }
}

void cv_merge_free(){
  kfree(cv_merge_empty_page);
}

void ksnap_merge(struct page * latest_page, unsigned int * local, struct page * ref_page, struct page * local_page){
  unsigned int * latest, * ref;
  int i=0;

  printk(KSNAP_LOG_LEVEL "pid %d MERGING %lu %p %lu %p\n", current->pid, page_to_pfn(latest_page), local, page_to_pfn(ref_page), ref_page);
  printk(KSNAP_LOG_LEVEL ".....first int %d", local[0]);
  prefetchw(local);
  if (ref_page!=NULL){
    ref = kmap_atomic(ref_page, KM_USER1);
    prefetchw(ref);
  }
  else{
    ref = cv_merge_empty_page;
  }

  if (!access_ok(VERIFY_READ, local, PAGE_SIZE)){
    printk(KSNAP_LOG_LEVEL "merge access failed for %p\n", local);
    BUG();
  }

  latest = kmap_atomic(latest_page, KM_USER0);

  cv_per_thread_debug_insert(0x666, 0);
  //cv_per_thread_debug_insert(latest, 2);
  cv_per_thread_debug_insert(local_page, 1);
  cv_per_thread_debug_insert(local, 2);
  
  //now do the diff
  for (;i<1024;++i){
    if (unlikely(latest[i]!=ref[i] && local[i]==ref[i])){
      local[i]=latest[i];
    }
  }
  //printk("MERGED counter %d debug_total %d index %d pid %d\n", counter, debug_total, ref_page->index, current->pid);
  kunmap_atomic(latest, KM_USER0);
  if (ref_page){
    kunmap_atomic(ref, KM_USER1);
  }

  //printk(KSNAP_LOG_LEVEL "DONE MERGING %p %p %p\n", latest_page, local, ref_page);
}
