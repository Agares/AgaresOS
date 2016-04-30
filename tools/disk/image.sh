DISK_IMAGE_PATH=dist/disk.img

mkdir -p dist

dd if=/dev/zero of=$DISK_IMAGE_PATH bs=512 count=64k

fdisk $DISK_IMAGE_PATH << EOF
n
p
1
2048
65535
a
w
EOF
fdisk -lu $DISK_IMAGE_PATH
losetup /dev/loop4 $DISK_IMAGE_PATH
losetup -o 1048576 /dev/loop5 $DISK_IMAGE_PATH
mkfs.ext2 /dev/loop5
mkdir -p /mnt/agos
mount -t ext2 /dev/loop5 /mnt/agos
cp -R loader/dist/boot/* /mnt/agos
cp -R kernel/dist/boot/* /mnt/agos
mkdir -p /mnt/agos/boot/grub/
grub2-install --target=i386-pc --root-directory=/mnt/agos --no-floppy \
	--modules="normal part_msdos ext2 multiboot" /dev/loop4
cat > /mnt/agos/boot/grub/grub.cfg << EOF
menuentry \"agos\" {
	set root=(hd0,msdos1)

	multiboot2 /loader.bin
	module2 /kernel.bin
}
EOF
umount /mnt/agos
losetup -d /dev/loop5
losetup -d /dev/loop4

chown $SUDO_USER:$SUDO_USER $DISK_IMAGE_PATH
