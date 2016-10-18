
SHELL=/bin/bash

ifndef CONVLOGGING
	CONVLOGGING = false
endif


.PHONY: tests

all : conversionlib conversionlib32 conversionmodule

libmm : 
	pushd source/lib/mm; \
	./compileAndInstall.sh; \
	popd;

conversionlib : libmm
	pushd source/lib/conversion; \
	make clean; \
	make; \
	make install CV_INSTALLDIR='/usr/lib'; \
	popd; \
	sudo cp source/scripts/find_snapshot_mapping.sh /usr/bin;

conversionlib32 : libmm
	pushd source/lib/conversion; \
	make clean; \
	make CV_LIB_ARCH='-m32' CONV_DETERM='-DCONV_DETERM'; \
        make install CV_INSTALLDIR='/lib32'; \
	popd; \
	sudo cp source/scripts/find_snapshot_mapping.sh /usr/bin;


conversionmodule :
	pushd source/module; \
	sudo ./install.sh y LOGGING=$(CONVLOGGING); \
	popd;

tests : conversionlib conversionmodule
	pushd tests; \
	make; \
	popd; 

clean : 
	pushd source/lib/conversion; \
	make clean; \
	popd;\
	pushd source/module; \
	sudo rm *.o; \
	popd;

