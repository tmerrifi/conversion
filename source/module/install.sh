sudo ./remove.sh
if [ $1 = 'y' ]
then
    make $2 $3 $4 $5 $6;
fi
sudo insmod ./ksnapmod.ko;
