
struct ksnap;
struct ksnap_user_data;

typedef enum {CV_HOOKS_COMMIT_ENTRY_SKIP=0, CV_HOOKS_COMMIT_ENTRY_COMMIT=1, CV_HOOKS_COMMIT_ENTRY_MERGE=2} cv_hooks_commit_type_t;
typedef enum {CV_HOOKS_UPDATE_ENTRY_SKIP=0, CV_HOOKS_UPDATE_ENTRY_UPDATE=1, CV_HOOKS_UPDATE_ENTRY_MERGE=2} cv_hooks_update_type_t;

/*Certain applications (determinism) may require code to fire when certain conversion events happen*/
struct conversion_hooks{
    void (*cv_on_commit_begin)(struct ksnap * cv, struct ksnap_user_data * cv_user, unsigned long flags);
    void (*cv_on_update_begin)(struct ksnap * cv, struct ksnap_user_data * cv_user, unsigned long flags);
    void (*cv_on_commit_entry)(struct ksnap * cv, struct ksnap_user_data * cv_user, unsigned int logical_page, cv_hooks_commit_type_t type );
    void (*cv_on_update_entry)(struct ksnap * cv, struct ksnap_user_data * cv_user, unsigned int logical_page, cv_hooks_update_type_t type );
    void (*cv_on_cow)(struct ksnap * cv, struct ksnap_user_data * cv_user, unsigned int logical_page);

};

#define CV_HOOKS_INIT(cv)                       \
    cv->hooks.cv_on_commit_begin=cv->hooks.cv_on_update_begin=cv->hooks.cv_on_commit_entry=cv->hooks.cv_on_update_entry=NULL;

#ifdef CV_HOOKS

#define CV_HOOKS_BEGIN_COMMIT(cv, cv_user, flags)        \
    if (cv->hooks.cv_on_commit_begin) \
        cv->hooks.cv_on_commit_begin(cv, cv_user, flags);

#define CV_HOOKS_BEGIN_UPDATE(cv, cv_user, flags)        \
    if (cv->hooks.cv_on_update_begin) \
        cv->hooks.cv_on_update_begin(cv, cv_user, flags);

#define CV_HOOKS_COMMIT_ENTRY(cv, cv_user, logical_page, type) \
    if (cv->hooks.cv_on_commit_entry) \
        cv->hooks.cv_on_commit_entry(cv, cv_user, logical_page, type);

#define CV_HOOKS_UPDATE_ENTRY(cv, cv_user, logical_page, type)   \
    if (cv->hooks.cv_on_update_entry) \
        cv->hooks.cv_on_update_entry(cv, cv_user, logical_page, type);

#define CV_HOOKS_COW(cv, cv_user, logical_page)   \
    if (cv->hooks.cv_on_cow) \
        cv->hooks.cv_on_cow(cv, cv_user, logical_page);


#else

#define CV_HOOKS_BEGIN_COMMIT(cv, cv_user, flags)        \

#define CV_HOOKS_BEGIN_UPDATE(cv, cv_user, flags)        \

#define CV_HOOKS_COMMIT_ENTRY(cv, cv_user, logical_page, type) \

#define CV_HOOKS_UPDATE_ENTRY(cv, cv_user, logical_page, type)   \

#define CV_HOOKS_COW(cv, cv_user, logical_page)   \


#endif
