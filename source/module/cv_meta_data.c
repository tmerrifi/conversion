
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/hardirq.h>
#include <asm/page_types.h>
#include <asm/uaccess.h>

#include "conversion.h"
#include "cv_meta_data.h"
#include "cv_pte.h"

void cv_meta_set_partial_updated_unique_pages(struct vm_area_struct * vma, uint32_t count){
    struct ksnap_meta_data_local * meta_data = (struct ksnap_meta_data_local *)(vma->vm_start - (PAGE_SIZE*META_LOCAL_OFFSET_FROM_SEGMENT));
    meta_data->partial_updated_unique_pages=count;
}

unsigned int cv_meta_get_partial_updated_unique_pages(struct vm_area_struct * vma){
    struct ksnap_meta_data_local * meta_data = (struct ksnap_meta_data_local *)(vma->vm_start - (PAGE_SIZE*META_LOCAL_OFFSET_FROM_SEGMENT));
    return meta_data->partial_updated_unique_pages;
}

unsigned int cv_meta_inc_partial_updated_unique_pages(struct vm_area_struct * vma, uint32_t inc_value){
    struct ksnap_meta_data_local * meta_data = (struct ksnap_meta_data_local *)(vma->vm_start - (PAGE_SIZE*META_LOCAL_OFFSET_FROM_SEGMENT));
    meta_data->partial_updated_unique_pages+=inc_value;
    return meta_data->partial_updated_unique_pages;
}


void cv_meta_set_dirty_page_count(struct vm_area_struct * vma, uint32_t count){
  struct ksnap_meta_data_local * meta_data = (struct ksnap_meta_data_local *)(vma->vm_start - (PAGE_SIZE*META_LOCAL_OFFSET_FROM_SEGMENT));
  meta_data->dirty_page_count=count;
}

void cv_meta_inc_dirty_page_count(struct vm_area_struct * vma){
    struct ksnap_meta_data_local * meta_data = (struct ksnap_meta_data_local *)(vma->vm_start - (PAGE_SIZE*META_LOCAL_OFFSET_FROM_SEGMENT));
    meta_data->dirty_page_count++;
}


void cv_meta_inc_updated_page_count(struct vm_area_struct * vma){
    struct ksnap_meta_data_local * meta_data = (struct ksnap_meta_data_local *)(vma->vm_start - (PAGE_SIZE*META_LOCAL_OFFSET_FROM_SEGMENT));
    meta_data->updated_pages++;
    
}

void cv_meta_set_updated_page_count(struct vm_area_struct * vma, uint32_t count){
    struct ksnap_meta_data_local * meta_data = (struct ksnap_meta_data_local *)(vma->vm_start - (PAGE_SIZE*META_LOCAL_OFFSET_FROM_SEGMENT));
    meta_data->updated_pages=count;
}

void cv_meta_set_merged_page_count(struct vm_area_struct * vma, uint32_t count){
    struct ksnap_meta_data_local * meta_data = (struct ksnap_meta_data_local *)(vma->vm_start - (PAGE_SIZE*META_LOCAL_OFFSET_FROM_SEGMENT));
    meta_data->merged_pages=count;
}

void cv_meta_set_partial_version_num(struct vm_area_struct * vma, unsigned int version){
    struct ksnap_meta_data_local * meta_data = (struct ksnap_meta_data_local *)(vma->vm_start - (PAGE_SIZE*META_LOCAL_OFFSET_FROM_SEGMENT));
    meta_data->partial_version_num=version;
}


struct ksnap_meta_data_local * __get_meta_local(struct vm_area_struct * vma){
  struct ksnap_meta_data_local * meta_data = ksnap_vma_to_userdata(vma)->meta_data;
  if (meta_data == NULL){
    meta_data = (struct ksnap_meta_data_local *)(vma->vm_start - (PAGE_SIZE*META_LOCAL_OFFSET_FROM_SEGMENT));
    ksnap_vma_to_userdata(vma)->meta_data=meta_data;
  }
  return meta_data;
}

struct ksnap_dirty_list_entry * __get_dirty_list(struct vm_area_struct * vma,  struct ksnap_meta_data_local * meta_data){
  struct ksnap_dirty_list_entry * dirty_list = ksnap_vma_to_userdata(vma)->dirty_list_bitmap;
  if (dirty_list == NULL){
    dirty_list = (struct ksnap_dirty_list_entry *)(vma->vm_start - (PAGE_SIZE*meta_data->meta_data_size) - (PAGE_SIZE*(META_LOCAL_OFFSET_FROM_SEGMENT-1)));
    ksnap_vma_to_userdata(vma)->dirty_list_bitmap=dirty_list;
  }
  return dirty_list;
}

void ksnap_meta_set_local_version(struct vm_area_struct * vma, unsigned int current_version){
  struct ksnap_meta_data_local * meta_data = (struct ksnap_meta_data_local *)(vma->vm_start - (PAGE_SIZE*META_LOCAL_OFFSET_FROM_SEGMENT));
  meta_data->snapshot_version_num=current_version;
}

unsigned int ksnap_meta_get_local_version(struct vm_area_struct * vma){
  struct ksnap_meta_data_local * meta_data = (struct ksnap_meta_data_local *)(vma->vm_start - (PAGE_SIZE*META_LOCAL_OFFSET_FROM_SEGMENT));
  return meta_data->snapshot_version_num;
}

//search the dirty list to see if a certain page is in there
unsigned char ksnap_meta_search_dirty_list(struct vm_area_struct * vma, unsigned long page_index){
  struct ksnap_meta_data_local * meta_data = __get_meta_local(vma);
  struct ksnap_dirty_list_entry * dirty_list = __get_dirty_list(vma, meta_data);
  int i=0;
  unsigned char result=0;

  if (meta_data->dirty_list_mode == DIRTY_LIST_LISTMODE){
    //loop through the list and find the page
    for (;i<meta_data->dirty_page_count;++i){
      //now set the bit for each page in the current list
      if (dirty_list[i].page_index == page_index){
	result=1;
	break;
      }
    }
  }
  else{
    result=test_bit(page_index, (unsigned long *)dirty_list);
  }

  return result;
}

unsigned int ksnap_meta_get_shared_version(struct vm_area_struct * vma){
  struct ksnap_meta_data_shared * meta_data = (struct ksnap_meta_data_shared *)(vma->vm_start - (PAGE_SIZE*META_SHARED_OFFSET_FROM_SEGMENT));
  return meta_data->snapshot_version_num;
}

//increment the version number that is mapped in by all segments
void ksnap_meta_inc_shared_version(struct vm_area_struct * vma){
  struct ksnap_meta_data_shared * meta_data = (struct ksnap_meta_data_shared *)(vma->vm_start - (PAGE_SIZE*META_SHARED_OFFSET_FROM_SEGMENT));
  meta_data->snapshot_version_num+=1;
}

//set the version number that is mapped in by all segments
void ksnap_meta_set_shared_version(struct vm_area_struct * vma, uint64_t version_num){
  struct ksnap_meta_data_shared * meta_data = (struct ksnap_meta_data_shared *)(vma->vm_start - (PAGE_SIZE*META_SHARED_OFFSET_FROM_SEGMENT));
  meta_data->snapshot_version_num=version_num;
}


//we have too many entries in our dirty page list...we need to covert it to a bitmap instead
void __convert_list_to_bitmap(struct ksnap_dirty_list_entry * dirty_list, struct ksnap_meta_data_local * meta_data){
  int i=0;
  unsigned int size_of_list_bytes = (meta_data->meta_data_size - 1) * PAGE_SIZE;
  unsigned int size_of_list_bits = size_of_list_bytes * 8;
  struct ksnap_dirty_list_entry * tmp_dirty_list = kmalloc(size_of_list_bytes, GFP_KERNEL);
  //since we're messing with the list...need to copy it over first
  memcpy(tmp_dirty_list, dirty_list, size_of_list_bytes);
  bitmap_zero((unsigned long *)dirty_list, size_of_list_bits);

  for (;i<meta_data->dirty_page_count;++i){
    //now set the bit for each page in the current list
    set_bit(tmp_dirty_list[i].page_index, (unsigned long *)dirty_list);
  }
  kfree(tmp_dirty_list);
}

void __ksnap_meta_add_dirty_list(struct ksnap_dirty_list_entry * dirty_list, struct ksnap_meta_data_local * meta_data, unsigned long cow_page_index){
  dirty_list[meta_data->dirty_page_count].page_index = cow_page_index;
  meta_data->dirty_page_count+=1;
  /*printk(KSNAP_LOG_LEVEL "the dirty page count is %d %p, index is %lu, pid %d\n", meta_data->dirty_page_count, &meta_data->dirty_page_count, cow_page_index, current->pid);*/
    if (meta_data->dirty_page_count >= meta_data->dirty_list_size){
    meta_data->dirty_list_mode = DIRTY_LIST_BITMAPMODE;
    __convert_list_to_bitmap(dirty_list, meta_data);
  }
}


void ksnap_meta_clear_dirty(struct vm_area_struct * vma){
  struct ksnap_meta_data_local * meta_data = (struct ksnap_meta_data_local *)(vma->vm_start - (PAGE_SIZE*META_LOCAL_OFFSET_FROM_SEGMENT));
  if (access_ok(VERIFY_WRITE,meta_data,PAGE_SIZE)){
    //printk("ok to write %d, atomic? %d\n", current->pid, in_atomic());
    meta_data->dirty_page_count=0;
    meta_data->dirty_list_mode = DIRTY_LIST_LISTMODE;
  }
  else{
    BUG();
  }
}

void ksnap_meta_add_dirty_page(struct vm_area_struct * vma, unsigned long cow_page_index){
  
  //start by computing the address of the meta page
  struct ksnap_meta_data_local * meta_data = (struct ksnap_meta_data_local *)(vma->vm_start - (PAGE_SIZE*META_LOCAL_OFFSET_FROM_SEGMENT));
  if (access_ok(VERIFY_WRITE, meta_data, PAGE_SIZE)){
    struct ksnap_dirty_list_entry * dirty_list = (struct ksnap_dirty_list_entry *)(vma->vm_start - (PAGE_SIZE*meta_data->meta_data_size) - (PAGE_SIZE*(META_LOCAL_OFFSET_FROM_SEGMENT-1)));
    if (meta_data->dirty_list_mode == DIRTY_LIST_LISTMODE){
      __ksnap_meta_add_dirty_list(dirty_list, meta_data, cow_page_index);
    }
    else{
      set_bit(cow_page_index, (unsigned long *)dirty_list);
    }
    }
  //printk(KERN_INFO "meta address %p %d %d\n", meta_data, meta_data->meta_data_size, meta_data->dirty_page_count);
}
