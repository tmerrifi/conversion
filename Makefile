
SHELL=/bin/bash

.PHONY: tests

all : conversionlib conversionmodule

conversionlib :
	pushd source/lib; \
	make; \
	make install; \
	popd;

conversionmodule :
	pushd source/module; \
	sudo ./install.sh y; \
	popd;

tests :
	pushd tests; \
	make; \
	popd; 
