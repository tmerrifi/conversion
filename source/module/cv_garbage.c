
#include "ksnap.h"
#include "cv_garbage.h"

void cv_garbage_final(struct ksnap * cv_seg){
  struct list_head * version_list_pos, * version_list_tmp_pos, * pte_list_entry_pos, * pte_list_entry_pos_tmp;
  struct snapshot_version_list * version_list_entry;
  struct snapshot_pte_list * pte_list_entry;
  struct page * old_page;

  //ok, lets walk the version list, find out of date versions
  list_for_each_prev_safe(version_list_pos, version_list_tmp_pos, &cv_seg->snapshot_pte_list->list){
    version_list_entry = list_entry(version_list_pos, struct snapshot_version_list, list);
      list_for_each_safe(pte_list_entry_pos, pte_list_entry_pos_tmp, &version_list_entry->pte_list->list){
	pte_list_entry = list_entry(pte_list_entry_pos, struct snapshot_pte_list, list);
	old_page = pfn_to_page(pte_list_entry->pfn);
	old_page->mapping=NULL;
	ClearPageDirty(old_page);
	SetPageSwapBacked(old_page);
	put_page(old_page);
	pte_list_entry->pfn=0xDEAD;
	list_del(pte_list_entry_pos);
	kmem_cache_free(cv_seg->pte_list_mem_cache, pte_list_entry);
      }
      BUG_ON(!list_empty(&version_list_entry->pte_list->list));
      list_del(version_list_pos);
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
  struct page * old_page;
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
	  old_page = pfn_to_page(pte_list_entry->pfn);
	  old_page->mapping=NULL;
	  ClearPageDirty(old_page);
	  SetPageSwapBacked(old_page);
	  put_page(old_page);
	  ++collected_count;
	  pte_list_entry->pfn=0xDEAD;
	  list_del(pte_list_entry_pos);
	  kmem_cache_free(cv_seg->pte_list_mem_cache, pte_list_entry);
	}
      }
      //BUG_ON(!list_empty(&version_list_entry->pte_list->list));
      //list_del(version_list_pos);
    }
  }
  cv_seg->committed_pages-=collected_count;
  atomic_set(&cv_seg->gc_thread_count, -1);
}
