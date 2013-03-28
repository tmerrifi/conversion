
#ifndef KSNAP_INIT
#define KSNAP_INIT

int ksnap_open (struct vm_area_struct * vma, unsigned long flags);

struct ksnap * ksnap_init_snapshot (struct address_space * mapping, struct vm_area_struct * vma);

int ksnap_tracking_on(struct vm_area_struct * vma);

int ksnap_tracking_off(struct vm_area_struct * vma);

#endif
