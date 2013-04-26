
SHELL=/bin/bash

.PHONY: tests

all : conversionlib conversionlib32 conversionmodule

libmm : 
	pushd source/lib/mm; \
	./compileAndInstall.sh; \
	popd;

conversionlib : libmm
	pushd source/lib/conversion; \
	make; \
	make install CV_INSTALLDIR='/usr/lib'; \
	popd;

conversionlib32 : libmm
	pushd source/lib/conversion; \
	make clean; \
	make CV_LIB_ARCH='-m32' CONV_DETERM='-DCONV_DETERM'; \
        make install CV_INSTALLDIR='/lib32'; \
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
