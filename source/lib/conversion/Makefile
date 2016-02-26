CFLAGS = -g -std=gnu99 -fPIC
SOURCES = sync.o ksnap.o time_util.o bitmap.o #cv_determ.o
LIBS = -pthread -lrt

#INSTALLDIR = /usr/lib
INSTALLLIB = /usr/local/include

all: dynlib

dynlib: $(SOURCES) #force_run
	gcc -shared $(CFLAGS) $(CV_LIB_ARCH) -o libksnap.so $(SOURCES) $(LIBS);

%.o: %.c
	gcc $(CFLAGS) $(CV_LIB_ARCH) -o $@ -c $< $(LIBS);

install:
	sudo cp libksnap.so $(CV_INSTALLDIR);\
	sudo cp *.h $(INSTALLLIB)

clean:
	rm -f *.o *.so;
