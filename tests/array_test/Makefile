
.PHONY: tests

SHELL=/bin/bash
objectfiles=arr_bench.o 
libs=-lmm -lrt -lksnap

all : arr_bench

arr_bench : bmharness.cpp $(objectfiles)
	g++ -DCV_UNIT_TESTS -o arr_bench bmharness.cpp $(objectfiles) $(libs)

%.o : %.cpp
<<<<<<< HEAD
	g++ -DCV_UNIT_TESTS -c -o $@ $< $(libs)
=======
	g++ -c -o $@ $< $(libs)
>>>>>>> 5146d6a919c3939e472e4a1304d0378002ed0972

tests :
	pushd ../../source/module; \
	sudo ./install.sh y; \
	popd; \
	sudo rm *.mem; \
	sudo rm *.sem; \
	sudo rm snapshot_stm.*; \
	sudo rm /dev/shm/*.sem; \
<<<<<<< HEAD
	sudo ./arr_bench -q 1 -m 400000 -p 8 -Q 8 -R 50 -X 10000 -N 200 -P 1;
=======
	sudo ./arr_bench -q 1 -m 2000000 -p 32 -Q 32 -R 50 -X 50000 -N 200 -P 1;
>>>>>>> 5146d6a919c3939e472e4a1304d0378002ed0972

clean : 
	rm *.o arr_bench;