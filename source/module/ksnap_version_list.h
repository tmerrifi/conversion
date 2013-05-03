
#ifndef KSNAP_VERSION_LIST
#define KSNAP_VERSION_LIST

#include <linux/radix-tree.h>
#include "conversion.h"

//remove_pte_entry_from_version_list
//delete_old_pte
/*removing an entry from a version. We first look it up in the radix tree which points to the entry*/
void remove_pte_entry_from_version_list(struct radix_tree_root * snapshot_page_tree, unsigned long index, struct ksnap * ksnap_segment);

void ksnap_version_list_debug_print(struct snapshot_version_list * version_list);

struct snapshot_pte_list * _snapshot_create_pte_list(void);

struct snapshot_version_list * _snapshot_create_version_list(void);

struct snapshot_version_list * cv_create_version_list_entry(void);

struct snapshot_pte_list * cv_version_list_copy_list_entry(struct ksnap * cv_seg, struct snapshot_pte_list * entry);

struct snapshot_pte_list * cv_version_list_lookup(struct ksnap * cv_seg, uint64_t index);

#endif
