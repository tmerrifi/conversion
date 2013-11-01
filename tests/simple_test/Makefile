
.PHONY: tests

SHELL=/bin/bash

all: simple

simple: simple.c
	gcc -g -fno-stack-protector -o simple simple.c -lrt -lksnap

new : 
	./simple;

tests : simple
	pushd ../../source/module; \
	sudo ./install.sh y; \
	popd; \
	sudo rm *.mem*; \
	./simple;

clean:
	rm simple;
