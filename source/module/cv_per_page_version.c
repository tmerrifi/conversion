

#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/slab.h>
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
#include <linux/hardirq.h>

#include "ksnap.h"
#include "cv_per_page_version.h"


struct cv_per_page_version * cv_per_page_version_init(uint32_t page_count){
  struct cv_per_page_version * ppv = kmalloc(sizeof(struct cv_per_page_version), GFP_KERNEL);
  ppv->entries = kmalloc(sizeof(struct cv_per_page_version_entry) * page_count, GFP_KERNEL);
  memset(ppv->entries, 0, sizeof(struct cv_per_page_version_entry) * page_count);
  return ppv;
}

uint32_t __commit_page_status(struct cv_per_page_version * ppv, uint32_t page_index){
  if(ppv->entries[page_index].interest_version == ppv->entries[page_index].actual_version){
    return __CV_PPV_SAFE;
  }
  else{
    return __CV_PPV_UNSAFE;
  }
}

uint32_t __commit_page_wait_status(struct cv_per_page_version * ppv, uint32_t page_index, uint64_t wait_version){
  if(ppv->entries[page_index].actual_version == wait_version){
    return __CV_PPV_SAFE;
  }
  else{
    return __CV_PPV_UNSAFE;
  }
}

//call this while holding mutex
void cv_per_page_version_walk(struct snapshot_pte_list * dirty_pages_list, struct snapshot_pte_list * wait_list, 
			      struct cv_per_page_version * ppv, uint64_t revision_number){
  struct list_head * pos, * tmp_pos;
  struct snapshot_pte_list * pte_entry;

  list_for_each_safe(pos, tmp_pos, &dirty_pages_list->list){
      pte_entry = list_entry(pos, struct snapshot_pte_list, list);
      if (__commit_page_status(ppv, pte_entry->page_index)==__CV_PPV_UNSAFE){
	pte_entry->wait_revision = ppv->entries[pte_entry->page_index].interest_version; //keep this so we can wait on interest to match actual later...
	list_del(&pte_entry->list);
	INIT_LIST_HEAD(&pte_entry->list);
	list_add(&pte_entry->list, &wait_list->list);
      }
      ppv->entries[pte_entry->page_index].interest_version=revision_number;
  }
}

struct snapshot_pte_list * cv_per_page_version_walk_unsafe(struct snapshot_pte_list * wait_list, struct cv_per_page_version * ppv){
  struct list_head * pos;
  struct snapshot_pte_list * pte_entry;

  list_for_each(pos, &wait_list->list){
    pte_entry = list_entry(pos, struct snapshot_pte_list, list);
    //check commit status
    if (__commit_page_wait_status(ppv, pte_entry->page_index, pte_entry->wait_revision) == __CV_PPV_SAFE){
      return pte_entry;
    }
  }
  return NULL;
}

void cv_per_page_version_update_version_entry(struct cv_per_page_version * ppv, struct snapshot_pte_list * version_list_entry){
  ppv->entries[version_list_entry->page_index].version_list_entry=version_list_entry;
}

struct snapshot_pte_list * cv_per_page_version_get_version_entry(struct cv_per_page_version * ppv, uint32_t index){
  return ppv->entries[index].version_list_entry;
}

void cv_per_page_version_update_actual_version(struct cv_per_page_version * ppv, uint32_t index, uint64_t version){
  ppv->entries[index].actual_version=version;
}
