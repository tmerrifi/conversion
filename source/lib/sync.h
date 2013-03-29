
#ifdef __cplusplus
 extern "C" {
#endif

struct sync_spin_barrier{
  unsigned int max;
  unsigned int begin;
  unsigned int end;
};

struct sync_spin_barrier * sync_spin_barrier_init(unsigned int count);

void sync_spin_barrier_wait(struct sync_spin_barrier * bar);

#ifdef __cplusplus
 }
#endif
