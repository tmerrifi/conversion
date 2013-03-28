rm *.o;
sudo ./remove.sh
if [ $1 = 'y' ]
then
    make;
fi
sudo insmod ./ksnapmod.ko;
