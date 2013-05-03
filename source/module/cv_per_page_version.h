
#ifndef CV_PER_PAGE_VERSION_H
#define CV_PER_PAGE_VERSION_H

#include "conversion.h"

struct cv_per_page_version_entry{
  uint64_t interest_version; //threads register their "interest" in committing this version
  uint64_t actual_version;  //what version is actually "committed"
  struct snapshot_pte_list * version_list_entry;
};

struct cv_per_page_version{
  struct cv_per_page_version_entry * entries;
};

struct cv_per_page_version_wait_list_entry{
  struct list_head list;
  uint32_t page_index;
};

#define __CV_PPV_SAFE 1
#define __CV_PPV_UNSAFE 2

struct cv_per_page_version * cv_per_page_version_init(uint32_t page_count);

void cv_per_page_version_walk(struct snapshot_pte_list * dirty_pages_list, struct snapshot_pte_list * wait_list, 
			      struct cv_per_page_version * ppv, uint64_t revision_number);

struct snapshot_pte_list * cv_per_page_version_walk_unsafe(struct snapshot_pte_list * wait_list, struct cv_per_page_version * ppv);

void cv_per_page_version_update_version_entry(struct cv_per_page_version * ppv, struct snapshot_pte_list * version_list_entry);

struct snapshot_pte_list * cv_per_page_version_get_version_entry(struct cv_per_page_version * ppv, uint32_t index);

void cv_per_page_version_update_actual_version(struct cv_per_page_version * ppv, uint32_t index, uint64_t version);

#endif
