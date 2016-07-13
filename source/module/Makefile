obj-m = ksnapmod.o
ksnapmod-y = cv_main.o ksnap_writer.o ksnap_version_list.o cv_commit.o cv_update.o cv_garbage.o cv_per_page_version.o cv_stats.o cv_init.o cv_meta_data.o cv_merge.o cv_pte.o cv_fork.o cv_close.o cv_revert.o cv_checkpoint.o cv_determinism.o cv_logging.o cv_decode.o cv_store_interpreter.o

ksnapmod-y += libudis86/decode.o libudis86/itab.o libudis86/syn-att.o libudis86/syn.o libudis86/syn-intel.o libudis86/udis86.o

#possible flags
#-DCONV_ATOMIC - Use atomic commit/update as opposed to 
#-DCONV_LOGGING_ON - Adds *lots* of logging information. Be careful when using this flag with SERIOUS workloads which make lots of conversion calls
#-DCV_STATS_ON - Generates statistics about number of calls to various conversion operations
#-DCV_HOOKS - Uses the hooks (function pointers) on certain events
#-DCV_EVENT_ON - Used for adding find grained event logging in the code...gets printed out when a thread closes the conversion segment
#-DCV_PROFILING_ON - Keeps track of information about each commit and then can be printed to the log from userspace
#-DCV_DETERMINISM - Used with consequence to support deterministic execution
#-DCV_LOGGING_DISABLED - disable logging

KBUILD_CFLAGS += -g -O3 --param max-unroll-times=16 -funroll-loops -Wno-declaration-after-statement -IcreateStoreInterpreterFunctions #-DCV_FORCE_LOGGING #-DCV_LOGGING_DISABLED #-DCV_FORCE_LOGGING #-DCV_DEBUG_MEMORY_ALLOC #-DCV_DETERMINISM -DCV_HOOKS

all: cv_main.c ksnap_writer.c ksnap_version_list.c cv_commit.c cv_update.c cv_garbage.c cv_per_page_version.c cv_stats.c cv_init.c cv_meta_data.c cv_merge.c cv_pte.c cv_fork.c cv_close.c cv_revert.c cv_checkpoint.c cv_determinism.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


# rules to build a userspace standalone store interpreter for testing

# TODO: clean this up and use proper globs for libudis86 files, here and for the kernel module (above)
si: cv_store_interpreter.c createStoreInterpreterFunctions/cv_store_interpreter_functions.c
	gcc -std=c99 -O0 -g -Wall -DTEST_INTERPRETER -I. -Ilibudis86 -IcreateStoreInterpreterFunctions $< libudis86/decode.c libudis86/itab.c libudis86/syn-att.c libudis86/syn.c libudis86/syn-intel.c libudis86/udis86.c -o $@

si-run: si
	./$<

si-clean:
	rm -f si
