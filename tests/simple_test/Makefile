
.PHONY: tests

SHELL=/bin/bash

all: simple

simple: simple.c
	gcc -g -fno-stack-protector -o simple simple.c ../common/common.o -lrt -lksnap -lpthread

new : 
	./simple;

tests : simple
	pushd ../../source/module; \
	sudo ./install.sh y; \
	popd; \
	sudo rm *.mem*; \
	for i in `seq 1 20`; do echo "test "$$i;./simple; done;

clean:
	rm simple; \
	sudo rm *.mem*;
