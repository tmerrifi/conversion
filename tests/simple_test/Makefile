
.PHONY: tests

SHELL=/bin/bash

all: simple

simple: 
	gcc -o simple simple.c -lrt -lksnap

tests : simple
	pushd ../../source/module; \
	sudo ./install.sh y; \
	popd; \
	sudo rm *.mem; \
	./simple;

clean:
	rm simple;