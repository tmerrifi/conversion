
.PHONY: tests

SHELL=/bin/bash

all: deferred_work

deferred_work: deferred_work.c
	gcc -g -fno-stack-protector -o deferred_work deferred_work.c ../common/common.o -lrt -lksnap -lpthread

new : 
	./deferred_work;

tests : deferred_work
	pushd ../../source/module; \
	sudo ./install.sh y; \
	popd; \
	sudo rm *.mem*; \
	./deferred_work;
	#for i in `seq 1 20`; do echo "test "$$i;./deferred_work; done;

clean:
	rm deferred_work; \
	sudo rm *.mem*;
