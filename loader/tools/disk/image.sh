DISK_IMAGE_PATH=dist/disk.img

dd if=/dev/zero of=$DISK_IMAGE_PATH bs=512 count=64k

fdisk $DISK_IMAGE_PATH << EOF
n
p
1
2048
65535
a
1
w
EOF
fdisk -lu $DISK_IMAGE_PATH
losetup /dev/loop0 $DISK_IMAGE_PATH
losetup -o 1048576 /dev/loop1 $DISK_IMAGE_PATH
mkfs.ext2 /dev/loop1
mkdir -p /mnt/agos
mount -t ext2 /dev/loop1 /mnt/agos
cp -R dist/boot/* /mnt/agos
dd if=/dev/zero of=/mnt/agos/zero.bin bs=512 count=1024
grub-install --root-directory=/mnt/agos --no-floppy \
	--modules="normal part_msdos ext2 multiboot" /dev/loop0
cat > /mnt/agos/boot/grub/grub.cfg << EOF
menuentry \"agos\" {
	set root=(hd0,msdos1)
	multiboot2 /kernel.bin
	module2 /zero.bin
}
EOF
umount /mnt/agos
losetup -d /dev/loop1
losetup -d /dev/loop0
