

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

#include <linux/vmalloc.h>

#include "conversion.h"
#include "cv_per_page_version.h"


struct cv_per_page_version * cv_per_page_version_init(uint32_t page_count){
  struct cv_per_page_version * ppv = kmalloc(sizeof(struct cv_per_page_version), GFP_KERNEL);
  ppv->entries = vmalloc(sizeof(struct cv_per_page_version_entry) * page_count);
  if (ppv->entries==NULL){
      printk(KERN_EMERG "whoops!, size was %lu\n", sizeof(struct cv_per_page_version_entry) * page_count);
      BUG();
  }
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

  //loop through all our dirty pages
  list_for_each_safe(pos, tmp_pos, &dirty_pages_list->list){
      //get the pte_entry
      pte_entry = list_entry(pos, struct snapshot_pte_list, list);
      //if the interest and actual aren't equal, we need to store the interest and move it into the right list
      if (__commit_page_status(ppv, pte_entry->page_index)==__CV_PPV_UNSAFE){
	pte_entry->wait_revision = ppv->entries[pte_entry->page_index].interest_version; //keep this so we can wait on interest to match actual later...
        //add it to the wait list
	list_del(&pte_entry->list);
	INIT_LIST_HEAD(&pte_entry->list);
	list_add(&pte_entry->list, &wait_list->list);
      }
      //regardless, set our own interest level
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

void cv_per_page_version_walk_unsafe_debug(struct snapshot_pte_list * wait_list, struct cv_per_page_version * ppv){
  struct list_head * pos;
  struct snapshot_pte_list * pte_entry;

  list_for_each(pos, &wait_list->list){
    pte_entry = list_entry(pos, struct snapshot_pte_list, list);
    //check commit status
    if (__commit_page_wait_status(ppv, pte_entry->page_index, pte_entry->wait_revision) == __CV_PPV_UNSAFE){
        printk(KERN_EMERG ".....unsafe %d: wait %llu actual %llu %p",
               pte_entry->page_index,
               pte_entry->wait_revision,
               ppv->entries[pte_entry->page_index].actual_version,
               pte_entry);
    }
  }
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

/*****LOGGING FUNCTIONS************/

//sliding window of checks on whether we would have benefited from logging
void cv_per_page_update_logging_diff_bitmap(struct cv_per_page_version * ppv, uint32_t page_index, int should_have_done_logging){
    ppv->entries[page_index].logging_diff_bitmap=((ppv->entries[page_index].logging_diff_bitmap<<1)|((should_have_done_logging) ? 1 : 0));
}

void cv_per_page_switch_to_logging(struct cv_per_page_version * ppv, uint32_t page_index){
    ppv->entries[page_index].type=DIRTY_LIST_ENTRY_TYPE_LOGGING;
    //set up the per page logging struture
    struct cv_per_page_logging_entry * pp_logging_entry = kmalloc(sizeof(struct cv_per_page_logging_entry), GFP_KERNEL);
    memset(pp_logging_entry, 0, sizeof(struct cv_per_page_logging_entry));
    ppv->entries[page_index].logging_entry = pp_logging_entry;
}

int cv_per_page_is_logging_page(struct cv_per_page_version * ppv, uint32_t page_index){
    return ppv->entries[page_index].type==DIRTY_LIST_ENTRY_TYPE_LOGGING;
}

uint8_t cv_per_page_get_logging_diff_bitmap(struct cv_per_page_version * ppv, uint32_t page_index){
    return ppv->entries[page_index].logging_diff_bitmap;
}

void cv_per_page_version_update_logging_entry(struct cv_per_page_version * ppv,
                                              uint32_t page_index,
                                              struct snapshot_pte_list * entry,
                                              uint64_t version_num,
                                              uint32_t line_index){
    struct cv_logging_entry * logging_entry = &entry->logging_entry;
    struct cv_per_page_logging_entry * pp_logging_entry = ppv->entries[page_index].logging_entry;
    if (cv_logging_is_full_page(logging_entry)){
        pp_logging_entry->page_entry=entry;
        pp_logging_entry->page_version=version_num;
    }
    else{
        pp_logging_entry->lines[line_index].version=version_num;
        pp_logging_entry->lines[line_index].line_entry=entry;
    }
    pp_logging_entry->max_version=version_num;
}

struct snapshot_pte_list * cv_per_page_version_get_logging_entry_and_version(struct cv_per_page_version * ppv, uint32_t page_index,
                                                                             uint32_t line_index, uint64_t * version_num, int is_page_level){
    //grab both the line version and the page level version
    struct cv_per_page_logging_entry * pp_logging_entry = ppv->entries[page_index].logging_entry;
    
    if (pp_logging_entry==NULL){
        return NULL;
    }
    else if ((is_page_level && pp_logging_entry->page_version == pp_logging_entry->max_version) ||
             (!is_page_level && pp_logging_entry->page_version > pp_logging_entry->lines[line_index].version)){
        //return the page level entry and version number
        *version_num = pp_logging_entry->page_version;
        return pp_logging_entry->page_entry;
    }
    else if (is_page_level){
        //we're page level, but there's a logging entry that's newer
        *version_num = pp_logging_entry->max_version;
        printk(KERN_EMERG "returning NULL\n");
        return NULL;
    }
    else{
        if (page_index==12){
            printk(KERN_EMERG "returning the line version, %lu, max version is %lu\n", pp_logging_entry->lines[line_index].version, pp_logging_entry->max_version);
        }
        //returning the line entry
        *version_num = pp_logging_entry->lines[line_index].version;
        return pp_logging_entry->lines[line_index].line_entry;
    }
}

struct snapshot_pte_list * cv_per_page_version_get_logging_line_entry(struct cv_per_page_version * ppv, uint32_t page_index,
                                                                      uint32_t line_index){
    struct cv_per_page_logging_entry * pp_logging_entry = ppv->entries[page_index].logging_entry;
    if (pp_logging_entry==NULL){
        return NULL;
    }
    else{
        return pp_logging_entry->lines[line_index].line_entry;
    }
}

void cv_per_page_version_clear_logging_line_entry(struct cv_per_page_version * ppv, uint32_t page_index,
                                                                      uint32_t line_index){
    struct cv_per_page_logging_entry * pp_logging_entry = ppv->entries[page_index].logging_entry;
    if (pp_logging_entry!=NULL){
        pp_logging_entry->lines[line_index].line_entry=NULL;
    }
}


struct snapshot_pte_list * cv_per_page_version_get_logging_page_entry(struct cv_per_page_version * ppv, uint32_t page_index){
    struct cv_per_page_logging_entry * pp_logging_entry = ppv->entries[page_index].logging_entry;
    if (pp_logging_entry==NULL){
        return NULL;
    }
    else{
        return pp_logging_entry->page_entry;
    }
}

