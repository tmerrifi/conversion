<<<<<<< HEAD
=======
rm *.o;
>>>>>>> 5146d6a919c3939e472e4a1304d0378002ed0972
sudo ./remove.sh
if [ $1 = 'y' ]
then
    make;
fi
sudo insmod ./ksnapmod.ko;
