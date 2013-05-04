
.PHONY: tests

SHELL=/bin/bash
objectfiles=arr_bench.o 
libs=-lmm -lrt -lksnap

all : arr_bench

arr_bench : bmharness.cpp $(objectfiles)
	g++ -o arr_bench bmharness.cpp $(objectfiles) $(libs)

%.o : %.cpp
	g++ -c -o $@ $< $(libs)

tests :
	pushd ../../source/module; \
	sudo ./install.sh y; \
	popd; \
	sudo rm *.mem; \
	sudo rm *.sem; \
	sudo rm snapshot_stm.*; \
	sudo rm /dev/shm/*.sem; \
	sudo ./arr_bench -q 1 -m 2000000 -p 4 -Q 4 -R 50 -X 500 -N 200 -P 1;

clean : 
	rm *.o arr_bench;
