sudo make;
sudo make install;
#sudo make modules_install;
sudo mkinitramfs -o /boot/initrd.img-2.6.37.6Shutter 2.6.37.6Shutter;
sudo grub-mkconfig -o /boot/grub/grub.cfg;
