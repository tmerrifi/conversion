
//if we reach 50 updated pages, we will flush the entire TLB instead of per entry
#define CV_TLB_FLUSH_MIN 50

static inline int conversion_flush_entire_tlb(struct list_head * version_list){
  struct list_head * pos;
  struct snapshot_version_list * vl_entry;
  unsigned int total_ptes;

  list_for_each_prev(pos, version_list){
    vl_entry = list_entry(pos, struct snapshot_version_list, list);
    total_ptes+=vl_entry->updated_ptes;
    if (total_ptes>CV_TLB_FLUSH_MIN)
      return 1;
  }
  return 0;
}
