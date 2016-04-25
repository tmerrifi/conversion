
obj-y = decode.o itab.o syn-att.o syn.o syn-intel.o udis86.o

all: *.c *.h
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean