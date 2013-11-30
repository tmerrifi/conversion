
#ifndef KSNAP_EXPORT_DIRTY
#define KSNAP_EXPORT_DIRTY

#include <linux/kernel.h>
#include <linux/mm.h>

struct ksnap_meta_data_local{
    unsigned int meta_data_size; //in pages
    unsigned char dirty_list_mode; //bitmap or list
    unsigned int dirty_page_count; 
    unsigned int dirty_list_size; //
    unsigned int snapshot_version_num; //the current version number
    unsigned int partial_version_num; //set after doing a partial update
    unsigned int updated_pages; //the number of pages updated by the last update
    unsigned int partial_updated_unique_pages; //unique updated pages from multiple calls to partial_update
    unsigned int merged_pages; //the number of pages updated by the last update
    unsigned int pid; 
};

struct ksnap_meta_data_shared{
  unsigned int snapshot_version_num;
};

struct ksnap_dirty_list_entry{
  unsigned int page_index;
};

#define DIRTY_LIST_LISTMODE 0
#define DIRTY_LIST_BITMAPMODE 1

//how many pages between the data and the metadata
#define META_LOCAL_OFFSET_FROM_SEGMENT 4
#define META_SHARED_OFFSET_FROM_SEGMENT 2

void cv_meta_set_partial_version_num(struct vm_area_struct * vma, unsigned int version);

void cv_meta_set_dirty_page_count(struct vm_area_struct * vma, uint32_t count);

void cv_meta_inc_dirty_page_count(struct vm_area_struct * vma);

void cv_meta_inc_updated_page_count(struct vm_area_struct * vma);

void cv_meta_set_updated_page_count(struct vm_area_struct * vma, uint32_t count);

void cv_meta_set_merged_page_count(struct vm_area_struct * vma, uint32_t count);

void cv_meta_set_partial_updated_unique_pages(struct vm_area_struct * vma, uint32_t count);

unsigned int cv_meta_inc_partial_updated_unique_pages(struct vm_area_struct * vma, uint32_t inc_value);

unsigned char ksnap_meta_search_dirty_list(struct vm_area_struct * vma, unsigned long page_index);

void ksnap_meta_add_dirty_page(struct vm_area_struct * vma, unsigned long cow_page_index);

void ksnap_meta_clear_dirty(struct vm_area_struct * vma);

void ksnap_meta_set_local_version(struct vm_area_struct * vma, unsigned int current_version);

unsigned int ksnap_meta_get_local_version(struct vm_area_struct * vma);

unsigned int ksnap_meta_get_shared_version(struct vm_area_struct * vma );

unsigned int cv_meta_get_partial_updated_unique_pages(struct vm_area_struct * vma);

//increment the version number that is mapped in by all segments
void ksnap_meta_inc_shared_version(struct vm_area_struct * vma);

void ksnap_meta_set_shared_version(struct vm_area_struct * vma, uint64_t version_num);

#endif
