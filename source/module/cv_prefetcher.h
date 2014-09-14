
#ifndef CV_PREFETCHER

#define CV_PREFETCHER


#define CV_PREFETCHER_STRONG_GET 3
#define CV_PREFETCHER_WEAK_GET 2
#define CV_PREFETCHER_WEAK_AVOID 1
#define CV_PREFETCHER_STRONG_AVOID 0

#define CV_PREFETCHER_NO_PAGE -1

struct cv_page_prefetch{
    uint8_t saturating_counter;
    uint16_t max_commit_count;
    int32_t page_index_to_fetch;
};

struct ksnap_user_data;

struct ksnap;

void cv_prefetcher_init(struct cv_page_prefetch * pf);

int cv_prefetcher_should_prefetch(int page_index, struct ksnap_user_data * cv_user_data);

int cv_prefetcher_get_page_index_to_prefetch(int page_index, struct ksnap_user_data * cv_user_data);

struct cv_page_prefetch * cv_prefetcher_get_entry_by_index(struct ksnap * cv_seg, int page_index);

//this function checks to see if the "page to fetch" actually got touched
int cv_prefetcher_update_page(int page_index, struct ksnap_user_data * cv_user_data);

void cv_prefetcher_on_fault(int page_index, struct ksnap_user_data * cv_user_data);

#endif
