done=`ls | grep libmm | wc | awk '{print $1}'`

if [ $done -eq 0 ]
then
	./configure --prefix=/usr --with-shm=MMFILE;
	make;
	sudo make install;
fi
