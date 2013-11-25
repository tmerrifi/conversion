
struct ksnap;

/*Certain applications (determinism) may require code to fire when certain conversion events happen*/
struct conversion_hooks{
    void (*cv_on_commit_begin)(struct ksnap *, unsigned long flags);
    void (*cv_on_update_begin)(struct ksnap *, unsigned long flags);
};

#define CV_HOOKS_INIT(cv)                       \
    cv->hooks.cv_on_commit_begin=cv->hooks.cv_on_update_begin=NULL;

#ifdef CV_HOOKS

#define CV_HOOKS_BEGIN_COMMIT(cv, flags)              \
    if (cv->hooks.cv_on_commit_begin) \
        cv->hooks.cv_on_commit_begin(cv, flags);

#define CV_HOOKS_BEGIN_UPDATE(cv, flags)              \
    if (cv->hooks.cv_on_update_begin) \
        cv->hooks.cv_on_update_begin(cv, flags);

#else

#define CV_HOOKS_BEGIN_COMMIT(cv, flags)              \

#define CV_HOOKS_BEGIN_UPDATE(cv, flags)              \

#endif
