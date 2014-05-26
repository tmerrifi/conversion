
SHELL=/bin/bash

.PHONY: common simple_test array_test

all : common simple_test partial


simple_test: common
	echo "SIMPLE TEST"; \
	printf "\n\n\n"; \
	pushd simple_test > /dev/null; \
	make; \
	make tests; \
	popd > /dev/null;

array_test : common
	echo "ARRAY TEST"; \
	printf "\n\n\n"; \
	pushd array_test > /dev/null; \
	make; \
	make tests; \
	popd > /dev/null;

common :
	pushd common > /dev/null; \
	make; \
	popd > /dev/null;

partial :
	echo "Partial Update and Merging Test"; \
	pushd partial_updates_test > /dev/null; \
	make; \
	make tests; \
	popd > /dev/null;
