obj-m = ksnapmod.o
ksnapmod-y = cv_main.o ksnap_writer.o ksnap_version_list.o cv_commit.o cv_commit_atomic.o cv_update_atomic.o cv_update.o cv_garbage.o cv_per_page_version.o cv_stats.o cv_init.o cv_meta_data.o cv_merge.o cv_pte.o cv_fork.o cv_close.o


#possible flags
#-DCONV_ATOMIC - Use atomic commit/update as opposed to 
#-DCONV_LOGGING_ON - Adds *lots* of logging information. Be careful when using this flag with SERIOUS workloads which make lots of conversion calls
#-DCV_STATS_ON - Generates statistics about number of calls to various conversion operations

KBUILD_CFLAGS += -g -O3 --param max-unroll-times=16 -funroll-loops -Wno-declaration-after-statement

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
