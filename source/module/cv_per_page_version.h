
#ifndef CV_PER_PAGE_VERSION_H
#define CV_PER_PAGE_VERSION_H

#include "conversion.h"

typedef enum _dirty_list_entry_t {DIRTY_LIST_ENTRY_TYPE_PAGE=0, DIRTY_LIST_ENTRY_TYPE_LOGGING=1} dirty_list_entry_t;

struct cv_per_page_logging_entry_line{
    uint64_t version;
    struct snapshot_pte_list * line_entry;
};

struct cv_per_page_logging_entry{
    struct cv_per_page_logging_entry_line lines[PAGE_SIZE/CV_LOGGING_LOG_SIZE];
    struct snapshot_pte_list * page_entry;
    uint64_t page_version;
    uint64_t max_version;
};

struct cv_per_page_version_entry{
    dirty_list_entry_t type; //what type is this?
    uint8_t logging_diff_bitmap; //keeps track of how often we perform the logging diff check and succeed
    uint64_t interest_version; //threads register their "interest" in committing this version
    uint64_t actual_version;  //what version is actually "committed"
    union{    
        struct snapshot_pte_list * version_list_entry;
        struct cv_per_page_logging_entry * logging_entry;
    };
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

void cv_per_page_update_logging_diff_bitmap(struct cv_per_page_version * ppv, uint32_t page_index, int should_have_done_logging);

void cv_per_page_switch_to_logging(struct cv_per_page_version * ppv, uint32_t page_index);

int cv_per_page_is_logging_page(struct cv_per_page_version * ppv, uint32_t page_index);

uint8_t cv_per_page_get_logging_diff_bitmap(struct cv_per_page_version * ppv, uint32_t page_index);


/*****LOGGING FUNCTIONS***********************/


void cv_per_page_version_update_logging_entry(struct cv_per_page_version * ppv,
                                              uint32_t page_index,
                                              struct snapshot_pte_list * entry,
                                              uint64_t version_num,
                                              uint32_t line_index);


struct snapshot_pte_list * cv_per_page_version_get_logging_entry(struct cv_per_page_version * ppv, uint32_t page_index, uint32_t line_index, uint64_t * version_num);

struct snapshot_pte_list * cv_per_page_version_get_logging_line_entry(struct cv_per_page_version * ppv, uint32_t page_index,
                                                                      uint32_t line_index);

struct snapshot_pte_list * cv_per_page_version_get_logging_page_entry(struct cv_per_page_version * ppv, uint32_t page_index);

#endif
