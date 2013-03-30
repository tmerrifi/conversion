make clean;
./configure --prefix=/usr --with-shm=MMFILE
make;
make test;
make install;
