obj-m = ksnapmod.o
ksnapmod-y = cv_main.o ksnap_writer.o ksnap_version_list.o cv_commit.o cv_update.o cv_garbage.o cv_per_page_version.o cv_stats.o cv_init.o cv_meta_data.o cv_merge.o cv_pte.o cv_fork.o cv_close.o

KBUILD_CFLAGS += -g -O3 --param max-unroll-times=16 -funroll-loops -DCV_PARALLEL -DCV_STATS_ON -Wno-declaration-after-statement

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
