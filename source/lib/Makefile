CFLAGS = -g -std=gnu99 -fPIC
#SOURCES = sync.o ftrace.o shmUtility.o ksnap_test_sub.o ksnap_test_owner.o memcpy_shm.o ksnap.o time_util.o bitmap.o
SOURCES = sync.o ksnap.o time_util.o bitmap.o

INSTALLDIR = /usr/lib

all: dynlib

dynlib: $(SOURCES) #force_run
	gcc -shared $(CFLAGS) $(CV_LIB_ARCH) -o libksnap.so $(SOURCES);\
	sudo cp libksnap.so $(INSTALLDIR);\
	sudo cp *.h /usr/local/include

%.o: %.c
	gcc $(CFLAGS) $(CV_LIB_ARCH) -o $@ -c $< 

#ksnap_test_sub.o: ksnap_test_sub.c
#	gcc $(CFLAGS) $(CV_LIB_ARCH) -o ksnap_test_sub.o -c ksnap_test_sub.c -lrt

#ksnap_test_owner.o: ksnap_test_owner.c
#	gcc $(CFLAGS) $(CV_LIB_ARCH) -o ksnap_test_owner.o -c ksnap_test_owner.c -lrt

#memcpy_shm.o: ksnap.o memcpy_shm.c memcpy_shm.h
#	gcc $(CFLAGS) $(CV_LIB_ARCH) -o memcpy_shm.o -c memcpy_shm.c

#sync.o: sync.c
#	gcc $(CFLAGS) $(CV_LIB_ARCH) -o sync.o -c sync.c -lrt

#ksnap.o: ksnap.c
#	gcc $(CFLAGS) $(CV_LIB_ARCH) -o ksnap.o -c ksnap.c -lrt

#time_util.o: time_util.c
#	gcc $(CFLAGS) $(CV_LIB_ARCH) -o time_util.o -c time_util.c

#ftrace.o: ftrace.c
#	gcc $(CFLAGS) $(CV_LIB_ARCH) -o ftrace.o -c ftrace.c

#bitmap.o: bitmap.c bitmap.h
#	gcc $(CFLAGS) $(CV_LIB_ARCH) -o bitmap.o -c bitmap.c

#shmUtility.o: shmUtility.c
#	gcc $(CFLAGS) $(CV_LIB_ARCH) -o shmUtility.o -c shmUtility.c -lrt

#force_run:
#	true

clean:
	rm -f *.o *.so;
