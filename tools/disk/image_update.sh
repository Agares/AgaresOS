DISK_IMAGE_PATH=dist/disk.img

losetup -o 1048576 /dev/loop3 $DISK_IMAGE_PATH
mount -t ext2 /dev/loop3 /mnt/agos
cp -Rf loader/dist/boot/* /mnt/agos
cp -Rf kernel/dist/boot/* /mnt/agos
umount /mnt/agos
losetup -d /dev/loop3
