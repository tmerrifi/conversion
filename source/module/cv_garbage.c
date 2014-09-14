
#include "conversion.h"
#include "cv_garbage.h"
#include "cv_debugging.h"
#include "cv_memory_accounting.h"
#include "cv_alloc_page.h"

void __cv_garbage_free_page(struct page * p){
    p->mapping=NULL;
    ClearPageDirty(p);
    SetPageSwapBacked(p);
    cv_page_debugging_inc_flag(p, CV_PAGE_DEBUG_GARBAGE_PUT_COUNT);
    put_page(p);
}

void __cv_garbage_free_page_to_list(struct cv_alloc_page * cap, struct page * p, struct list_head * list){
    p->mapping=NULL;
    ClearPageDirty(p);
    SetPageSwapBacked(p);
    cv_page_debugging_inc_flag(p, CV_PAGE_DEBUG_GARBAGE_PUT_COUNT);
    cv_alloc_page_prep_for_list(p);
    if (page_mapcount(p) > 0){
        printk(KERN_EMERG "UHOH!!!! %p\n");
    }

    if (list!=NULL){
        list_add(&p->lru, list); 
    }
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
            cv_memory_accounting_dec_pages(cv_seg);
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

  //printk(KERN_EMERG "Starting GC %d", low_version);

  //ok, lets walk the version list, find out of date versions
  list_for_each_prev_safe(version_list_pos, version_list_tmp_pos, &cv_seg->snapshot_pte_list->list){
      //validate
      if (current_seq_num!=cv_seg->gc_seq_num){
          goto out;
      }
      
      version_list_entry = list_entry(version_list_pos, struct snapshot_version_list, list);

      //if there is no committer, then something is wrong...dip out
      if (version_list_entry->committer==NULL){
          continue;
      }

#ifdef CV_USE_PAGE_ALLOC_LISTS
      struct cv_alloc_page * cap=&(ksnap_vma_to_userdata(version_list_entry->committer)->cap);
      int free_list_space=cv_alloc_page_list_free_space(cap);
      int elements_added=0;
      struct list_head page_alloc_list_head;
      INIT_LIST_HEAD(&page_alloc_list_head);
      /*printk(KERN_EMERG "GC: Beginning version %d free space %d committer %p low_version %d\n", 
        version_list_entry->version_num, free_list_space, version_list_entry->committer, low_version);*/
#endif

      if (version_list_entry->version_num + 5ULL < low_version && version_list_pos->prev != &cv_seg->snapshot_pte_list->list ){
          list_for_each_safe(pte_list_entry_pos, pte_list_entry_pos_tmp, &version_list_entry->pte_list->list){
              pte_list_entry = list_entry(pte_list_entry_pos, struct snapshot_pte_list, list);
              if (pte_list_entry->obsolete_version < cv_seg->committed_version_num){
                  //validate
                  if (current_seq_num!=cv_seg->gc_seq_num){
                      goto out;
                  }
                  the_page = pfn_to_page(pte_list_entry->pfn);
#ifdef CV_USE_PAGE_ALLOC_LISTS
                  if (elements_added<free_list_space){
                      __cv_garbage_free_page_to_list(cap, the_page, &page_alloc_list_head);
                      ++elements_added;
                  }
                  else{
                      __cv_garbage_free_page(the_page);
                  }
#else
                  __cv_garbage_free_page(the_page);
#endif

                  ++collected_count;
                  version_list_entry->num_of_entries--;
                  list_del(pte_list_entry_pos);
                  kmem_cache_free(cv_seg->pte_list_mem_cache, pte_list_entry);
                  cv_memory_accounting_dec_pages(cv_seg);
              }
          }
          //list_del(version_list_pos);
          //kfree(version_list_entry);
      }

#ifdef CV_USE_PAGE_ALLOC_LISTS
      if (elements_added>0){
          cv_alloc_page_append_pages(cap, &page_alloc_list_head, elements_added);
          //cv_alloc_page_print_list(cap, current->pid);
      }
#endif        

  }
  
 out:
  //printk(KERN_EMERG " LEAVING!!!! collected %d\n", collected_count);
  //reduce the total number of allocated pages. TODO: don't we don't need an atomic op here?
  cv_seg->committed_pages-=collected_count;
  atomic_set(&cv_seg->gc_thread_count, -1);
}
