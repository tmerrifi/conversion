SHELL=/bin/bash

.PHONY=test

all: partial

partial: partial.c
	gcc -std=gnu99 -g -o partial partial.c ../common/common.o -lksnap -lpthread

clean:
	rm partial; \
	rm *.mem*;

tests:
	for i in `seq 1 100`; do ./partial > /tmp/out$i; cat /tmp/out$i | grep FAIL > /tmp/fails; done; \
	if [ `cat /tmp/fails | wc -l | awk '{print $0}'` -gt 0 ]; then echo "FAILED"; else echo "SUCCESS"; fi;
