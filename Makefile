
SHELL=/bin/bash

.PHONY: tests

all : conversionlib conversionmodule

libmm : 
	pushd source/lib/mm; \
	./compileAndInstall.sh; \
	popd;

conversionlib : libmm
	pushd source/lib/conversion; \
	make; \
	make install; \
	popd;

conversionmodule :
	pushd source/module; \
	sudo ./install.sh y; \
	popd;

tests : conversionlib conversionmodule
	pushd tests; \
	make; \
	popd; 

clean : 
	pushd source/lib/conversion; \
	make clean; \
	popd;	
