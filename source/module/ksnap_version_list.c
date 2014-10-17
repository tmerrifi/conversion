

#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/rmap.h>
#include <linux/pagemap.h>
#include <linux/list.h>
#include <linux/swap.h>

#include "conversion.h"
#include "ksnap_version_list.h"


struct snapshot_pte_list * _snapshot_create_pte_list(){
  struct snapshot_pte_list * pte_list = kmalloc(sizeof(struct snapshot_pte_list), GFP_KERNEL);
  INIT_LIST_HEAD(&pte_list->list);
  atomic_set(&pte_list->gotten, 0);
  return pte_list;
}

struct snapshot_version_list * cv_create_version_list_entry(){
  struct snapshot_version_list * version_entry;
  version_entry = kmalloc(sizeof(struct snapshot_version_list), GFP_KERNEL);
  INIT_LIST_HEAD(&version_entry->list);
  version_entry->pte_list = _snapshot_create_pte_list();
  atomic_set(&version_entry->ref_c, 0);
  version_entry->version_num=MAX_VERSION_NUM;
  version_entry->visible=0;
  atomic_set(&version_entry->gotten, 0);
  return version_entry;
}


struct snapshot_version_list * _snapshot_create_version_list(){
  struct snapshot_version_list * version_list, * version_entry;
  version_list = kmalloc(sizeof(struct snapshot_version_list), GFP_KERNEL);
  version_list->pte_list=NULL;
  atomic_set(&version_list->ref_c, 0);
  INIT_LIST_HEAD(&version_list->list);
  //now we need to add our first entry
  version_entry = kmalloc(sizeof(struct snapshot_version_list), GFP_KERNEL);
  INIT_LIST_HEAD(&version_entry->list);
  version_entry->pte_list = _snapshot_create_pte_list();
  atomic_set(&version_entry->ref_c, 0);
  version_list->uncommitted_version_entry=version_entry;
  version_entry->updated_ptes=0;
  version_entry->visible=0;
  //add the entry to the list
  list_add(&version_entry->list, &version_list->list);
  //printk("head of list %p, first entry %p\n", version_list, version_entry);
  return version_list;
}

//print out everything in the version list
void ksnap_version_list_debug_print(struct snapshot_version_list * version_list){
  struct list_head * version_entry_lh;
  struct list_head * page_entry_lh;
  struct snapshot_version_list * version_entry;
  struct snapshot_pte_list * page_entry;
  int count=0;

  printk(KSNAP_LOG_LEVEL "\n\nDEBUG VERSION LIST: ");
  if(version_list){
    list_for_each(version_entry_lh,&version_list->list){
      version_entry=list_entry( version_entry_lh, struct snapshot_version_list, list);
      //now loop through the page_list!
      printk(KSNAP_LOG_LEVEL "\n version %d visible %d--->", version_entry->version_num, version_entry->visible);
      if (version_entry && version_entry->pte_list){
	list_for_each(page_entry_lh, &version_entry->pte_list->list){
	  page_entry = list_entry(page_entry_lh, struct snapshot_pte_list, list);
	  if (page_entry){
	    printk(KSNAP_LOG_LEVEL "    %lu ,",page_entry->page_index);
	  }
	  ++count;
	}
      }
    }
  }
  printk(KSNAP_LOG_LEVEL " : size is %d\n\n", count);
}


void cv_version_list_calc_happens_before(struct snapshot_version_list * version_list, struct ksnap_user_data * cv_user){
    struct list_head * version_entry_lh;
    struct list_head * page_entry_lh;
    struct snapshot_version_list * version_entry;
    struct snapshot_pte_list * page_entry;
    int count=0;
    unsigned int local_tag=cv_meta_get_local_tag(cv_user->vma);
    if(version_list){

        bitmap_zero(cv_user->bit_array, (1<<18));

        list_for_each(version_entry_lh,&version_list->list){
            version_entry=list_entry( version_entry_lh, struct snapshot_version_list, list);
            //now loop through the page_list!
            if (version_entry && version_entry->pte_list && !cv_update_gotten_bitmap_isset(&version_entry->gotten, cv_user->consequence_id)){
                if (version_entry->consequence_id==cv_user->consequence_id){
                    cv_update_gotten_bitmap(&version_entry->gotten, cv_user->consequence_id);
                    continue;
                }

                uint32_t list_gotten_count=0;
                list_for_each(page_entry_lh, &version_entry->pte_list->list){
                    page_entry = list_entry(page_entry_lh, struct snapshot_pte_list, list);
                    if ( page_entry->page_index >= (1<<18) ){
                        printk(KERN_EMERG "index %d", page_entry->page_index);
                    }
                    
                    BUG_ON((page_entry->page_index >= (1<<18)));
                    if (page_entry && !cv_update_gotten_bitmap_isset(&page_entry->gotten, cv_user->consequence_id)){
                        //we haven't yet retrieved this guy
                        uint32_t committer_conseq_id=version_entry->consequence_id;
                        //test happens-before
                        if (version_entry->vector_clock[committer_conseq_id] <=
                            cv_user->vector_clock[committer_conseq_id]){
                            if (!test_bit(page_entry->page_index, cv_user->bit_array)){
                                //all good
                                set_bit(page_entry->page_index, cv_user->bit_array);
                                if (!cv_user->ignore_after_fork){
                                    cv_user->happens_before_counter++;
                                }
                                if (cv_user->consequence_id==1){
                                    //printk(KERN_EMERG "HB: %d retrieved page %d from version %llu tag %d\n", 
                                    //     cv_user->consequence_id, page_entry->page_index, version_entry->version_num, local_tag);
                                }
                            }
                            //set this no matter what
                            cv_update_gotten_bitmap(&page_entry->gotten, cv_user->consequence_id);
                        }
                        else{
                            if (cv_user->consequence_id==1){
                                //printk(KERN_EMERG "index bit was set, index %u, pfn %llu, committer %d, ours %d\n", 
                                //     page_entry->page_index, page_entry->pfn, version_entry->consequence_id, cv_user->consequence_id);
                            }
                            
                        }
                    }
                    else if (page_entry){
                        ++list_gotten_count;
                        if (list_gotten_count==version_entry->num_of_entries){
                            cv_update_gotten_bitmap(&version_entry->gotten, cv_user->consequence_id);
                        }

                        if (cv_user->consequence_id==1){
                            //long gotten=atomic64_read(&page_entry->gotten);
                            //printk(KERN_EMERG "thread bit was set, index %u, pfn %llu, committer %d, ours %d gotten %lu\n", 
                            //     page_entry->page_index, page_entry->pfn, version_entry->consequence_id, cv_user->consequence_id, gotten);
                        }
                    }
                }
            }
        }
    }
    cv_user->ignore_after_fork=0;
    if (cv_user->consequence_id==1){
        //printk(KERN_EMERG "DONE");
    }
}

void remove_pte_entry_from_version_list(struct radix_tree_root * snapshot_page_tree, unsigned long index, struct ksnap * ksnap_segment){
	
  struct snapshot_pte_list * pte_entry; 
  struct list_head * pte_entry_ls;
  
  //try and delete from the pte radix tree
  if ((pte_entry_ls = radix_tree_delete(snapshot_page_tree, index))){
    
    pte_entry = list_entry(pte_entry_ls, struct snapshot_pte_list, list);
    
    /*if (pte_entry->page_index%50==0){
      printk(KSNAP_LOG_LEVEL "PID %d REMOVING index %d page %p \n",
	     current->pid, pte_entry->page_index, pfn_to_page(pte_entry->pfn));
	     }*/
    list_del(pte_entry_ls);
    //kfree(pte_entry);
    kmem_cache_free(ksnap_segment->pte_list_mem_cache, pte_entry);
  }
}

struct snapshot_pte_list * cv_version_list_lookup(struct ksnap * cv_seg, uint64_t index){
  struct snapshot_pte_list * pte_entry; 
  struct list_head * pte_entry_ls;
  
  pte_entry=NULL;
  spin_lock(&cv_seg->snapshot_page_tree_lock);
  pte_entry_ls=radix_tree_lookup(&cv_seg->snapshot_page_tree, index);
  spin_unlock(&cv_seg->snapshot_page_tree_lock);
  if (pte_entry_ls){
    pte_entry = list_entry(pte_entry_ls, struct snapshot_pte_list, list);
  }
  return pte_entry;
}

struct snapshot_pte_list * cv_version_list_copy_list_entry(struct ksnap * cv_seg, struct snapshot_pte_list * entry){
  struct snapshot_pte_list * new_entry = kmem_cache_alloc(cv_seg->pte_list_mem_cache, GFP_KERNEL);
  memcpy(new_entry, entry, sizeof(struct snapshot_pte_list));
  INIT_LIST_HEAD(&new_entry->list);
  return new_entry;
}

