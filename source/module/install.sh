sudo ./remove.sh
if [ $1 = 'y' ]
then
    make;
fi
#sudo insmod ./ksnapmod.ko;
sudo mkdir -p /lib/modules/`uname -r`/kernel/conversion;
sudo cp ksnapmod.ko /lib/modules/`uname -r`/kernel/conversion;
sudo depmod -a;
sudo insmod /lib/modules/`uname -r`/kernel/conversion/ksnapmod.ko;
