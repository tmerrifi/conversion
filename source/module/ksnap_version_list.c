

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
  return pte_list;
}

struct snapshot_version_list * cv_create_version_list_entry(){
  struct snapshot_version_list * version_entry;
  version_entry = kmalloc(sizeof(struct snapshot_version_list), GFP_KERNEL);
  INIT_LIST_HEAD(&version_entry->list);
  version_entry->pte_list = _snapshot_create_pte_list();
  atomic_set(&version_entry->ref_c, 0);
  version_entry->version_num=~(0x0);
  version_entry->visible=0;
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

  trace_printk("\n\nDEBUG VERSION LIST: ");
  printk("\n\nDEBUG VERSION LIST: ");
  if(version_list){
    list_for_each(version_entry_lh,&version_list->list){
      version_entry=list_entry( version_entry_lh, struct snapshot_version_list, list);
      //now loop through the page_list!
      trace_printk("\n list %p--->", version_entry);
      printk("\n list %p--->", version_entry);
      if (version_entry && version_entry->pte_list){
	list_for_each(page_entry_lh, &version_entry->pte_list->list){
	  page_entry = list_entry(page_entry_lh, struct snapshot_pte_list, list);
	  if (page_entry){
	    trace_printk("%lu ,",page_entry->page_index);
	    printk("%lu ,",page_entry->page_index);
	  }
	  ++count;
	}
      }
    }
  }
  trace_printk(" : size is %d\n\n", count);
  printk(" : size is %d\n\n", count);
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
  pte_entry_ls=radix_tree_lookup(&cv_seg->snapshot_page_tree, index);
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

