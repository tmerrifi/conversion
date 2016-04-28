
#include "conversion.h"
#include "cv_garbage.h"
#include "cv_debugging.h"
#include "cv_memory_accounting.h"

void __cv_garbage_free_page(struct page * p){
    p->mapping=NULL;
    ClearPageDirty(p);
    SetPageSwapBacked(p);
    cv_page_debugging_inc_flag(p, CV_PAGE_DEBUG_GARBAGE_PUT_COUNT);
    put_page(p);
}

int __gc_page(struct cv_page_entry * page_entry, struct ksnap * cv_seg, uint64_t obsolete_version){
    struct page * the_page;
    if (obsolete_version < cv_seg->committed_version_num){
        the_page = pfn_to_page(page_entry->pfn);
        __cv_garbage_free_page(the_page);
        cv_memory_accounting_dec_pages(cv_seg);
        return 1;
    }
    else{
        return 0;
    }
}

void cv_garbage_final(struct ksnap * cv_seg){
    struct list_head * version_list_pos, * version_list_tmp_pos, * pte_list_entry_pos, * pte_list_entry_pos_tmp;
    struct snapshot_version_list * version_list_entry;
    struct snapshot_pte_list * pte_list_entry;
    struct page * old_page;
    struct cv_page_entry * page_entry;
    struct cv_logging_entry * logging_entry;
    int counter;
    
    //ok, lets walk the version list, find out of date versions
    list_for_each_prev_safe(version_list_pos, version_list_tmp_pos, &cv_seg->snapshot_pte_list->list){
        version_list_entry = list_entry(version_list_pos, struct snapshot_version_list, list);
        list_for_each_safe(pte_list_entry_pos, pte_list_entry_pos_tmp, &version_list_entry->pte_list->list){
            pte_list_entry = list_entry(pte_list_entry_pos, struct snapshot_pte_list, list);
            if (pte_list_entry->type==CV_DIRTY_LIST_ENTRY_TYPE_PAGING){
                page_entry=cv_list_entry_get_page_entry(pte_list_entry);
                old_page = pfn_to_page(page_entry->pfn);
                __cv_garbage_free_page(old_page);
                cv_memory_accounting_dec_pages(cv_seg);
            }
            else{
                //handle logging entry
                logging_entry=cv_list_entry_get_logging_entry(pte_list_entry);
                if (logging_entry->data_len==PAGE_SIZE){
                    kfree(logging_entry->data);
                }
                else{
                    //need to free to slab allocator
                }
            }
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
  uint64_t low_version = MAX_VERSION_NUM;
  uint64_t collected_count = 0;

  garbage_work = container_of(work, struct cv_garbage_work, work);
  cv_seg = garbage_work->cv_seg;

  int pid=-1;

  uint64_t current_seq_num = cv_seg->gc_seq_num;

  //find lowest version still held on to
  list_for_each(users_pos, &cv_seg->segment_list){
    user_data = list_entry(users_pos, struct ksnap_user_data, segment_list);
    if (user_data->version_num < low_version && user_data->status == CV_USER_STATUS_AWAKE){
      low_version = user_data->version_num;
      pid=user_data->id;
    }
  }

  if (low_version==MAX_VERSION_NUM){
      goto out;
  }

  down(&cv_seg->sem_gc);
  
  //ok, lets walk the version list, find out of date versions
  list_for_each_prev_safe(version_list_pos, version_list_tmp_pos, &cv_seg->snapshot_pte_list->list){
      //validate
      if (current_seq_num!=cv_seg->gc_seq_num){
          goto out;
      }
      version_list_entry = list_entry(version_list_pos, struct snapshot_version_list, list);
      if (version_list_entry->version_num + 5ULL < low_version && version_list_pos->prev != &cv_seg->snapshot_pte_list->list ){
          list_for_each_safe(pte_list_entry_pos, pte_list_entry_pos_tmp, &version_list_entry->pte_list->list){
              pte_list_entry = list_entry(pte_list_entry_pos, struct snapshot_pte_list, list);
              //validate
              if (current_seq_num!=cv_seg->gc_seq_num){
                  goto out;
              }
              if (pte_list_entry->type==CV_DIRTY_LIST_ENTRY_TYPE_PAGING &&
                  __gc_page(cv_list_entry_get_page_entry(pte_list_entry),cv_seg,pte_list_entry->obsolete_version)){
                  //collect a page
                  ++collected_count;
                  version_list_entry->num_of_entries--;
                  list_del(pte_list_entry_pos);
                  kmem_cache_free(cv_seg->pte_list_mem_cache, pte_list_entry);
              }
              else if (pte_list_entry->type==CV_DIRTY_LIST_ENTRY_TYPE_LOGGING){
                  BUG();
              }

          }
          //list_del(version_list_pos);
          //kfree(version_list_entry);
      }
  }
  
 out:
  //printk(KERN_EMERG " LEAVING!!!! collected %d\n", collected_count);
  //reduce the total number of allocated pages. TODO: don't we don't need an atomic op here?
  cv_seg->committed_pages-=collected_count;
  atomic_set(&cv_seg->gc_thread_count, -1);
  up(&cv_seg->sem_gc);
}
