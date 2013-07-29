
SHELL=/bin/bash

.PHONY: simple_test array_test

all : simple_test array_test

simple_test:
	echo "SIMPLE TEST"; \
	printf "\n\n\n"; \
	pushd simple_test; \
	make; \
	make tests; \
	popd;

array_test :
	echo "ARRAY TEST"; \
	printf "\n\n\n"; \
	pushd array_test; \
	make; \
	make tests; \
	popd;