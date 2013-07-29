
#include "conversion.h"
#include "cv_garbage.h"
#include "cv_debugging.h"

void __cv_garbage_free_page(struct page * p){
    p->mapping=NULL;
    ClearPageDirty(p);
    SetPageSwapBacked(p);
    cv_page_debugging_inc_flag(p, CV_PAGE_DEBUG_GARBAGE_PUT_COUNT);
    put_page(p);
}

void cv_garbage_final(struct ksnap * cv_seg){
    struct list_head * version_list_pos, * version_list_tmp_pos, * pte_list_entry_pos, * pte_list_entry_pos_tmp, * old_prev;
  struct snapshot_version_list * version_list_entry;
  struct snapshot_pte_list * pte_list_entry;
  struct page * old_page;
  int counter;

  old_prev=NULL;

  //ok, lets walk the version list, find out of date versions
  list_for_each_prev_safe(version_list_pos, version_list_tmp_pos, &cv_seg->snapshot_pte_list->list){
    version_list_entry = list_entry(version_list_pos, struct snapshot_version_list, list);
      list_for_each_safe(pte_list_entry_pos, pte_list_entry_pos_tmp, &version_list_entry->pte_list->list){
	pte_list_entry = list_entry(pte_list_entry_pos, struct snapshot_pte_list, list);
	if (pte_list_entry->addr==0){
            BUG();
        }
        old_prev = pte_list_entry_pos;
	old_page = pfn_to_page(pte_list_entry->pfn);
	__cv_garbage_free_page(old_page);
	list_del(pte_list_entry_pos);
	kmem_cache_free(cv_seg->pte_list_mem_cache, pte_list_entry);
      }
      BUG_ON(!list_empty(&version_list_entry->pte_list->list));
      list_del(version_list_pos);
      kfree(version_list_entry);
  }

}




void cv_garbage_collection(struct work_struct * work){
  struct list_head * version_list_pos, * version_list_tmp_pos, * pte_list_entry_pos, * pte_list_entry_pos_tmp;
  struct cv_garbage_work * garbage_work;
  struct ksnap * cv_seg;
  struct ksnap_user_data * user_data;
  struct list_head * users_pos;
  struct snapshot_version_list * version_list_entry;
  struct snapshot_pte_list * pte_list_entry;
  struct page * the_page;
  uint64_t low_version = ~(0x0);
  uint64_t collected_count = 0;

  garbage_work = container_of(work, struct cv_garbage_work, work);
  cv_seg = garbage_work->cv_seg;

  //find lowest version still held on to
  list_for_each(users_pos, &cv_seg->segment_list){
    user_data = list_entry(users_pos, struct ksnap_user_data, segment_list);
    if (user_data->version_num < low_version){
      low_version = user_data->version_num;
    }
  }

  //ok, lets walk the version list, find out of date versions
  list_for_each_prev_safe(version_list_pos, version_list_tmp_pos, &cv_seg->snapshot_pte_list->list){
    version_list_entry = list_entry(version_list_pos, struct snapshot_version_list, list);
    if (version_list_entry->version_num + 10 < low_version){
      list_for_each_safe(pte_list_entry_pos, pte_list_entry_pos_tmp, &version_list_entry->pte_list->list){
	pte_list_entry = list_entry(pte_list_entry_pos, struct snapshot_pte_list, list);
	if (pte_list_entry->obsolete_version < cv_seg->committed_version_num){ 
	  the_page = pfn_to_page(pte_list_entry->pfn);
          __cv_garbage_free_page(the_page);
	  ++collected_count;
          version_list_entry->num_of_entries--;
	  list_del(pte_list_entry_pos);
	  kmem_cache_free(cv_seg->pte_list_mem_cache, pte_list_entry);
	}
      }
    }
  }
  //reduce the total number of allocated pages. TODO: don't we don't need an atomic op here?
  cv_seg->committed_pages-=collected_count;
  atomic_set(&cv_seg->gc_thread_count, -1);
}
