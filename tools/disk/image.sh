DISK_IMAGE_PATH=dist/disk.img

dd if=/dev/zero of=$DISK_IMAGE_PATH bs=512 count=64k

sudo fdisk $DISK_IMAGE_PATH << EOF
n
p
1
2048
65535
a
1
w
EOF
sudo fdisk -lu $DISK_IMAGE_PATH
sudo losetup /dev/loop0 $DISK_IMAGE_PATH
sudo losetup -o 1048576 /dev/loop1 $DISK_IMAGE_PATH
sudo mkfs.ext2 /dev/loop1
sudo mount -t ext2 /dev/loop1 /mnt/
sudo cp -R dist/boot/* /mnt/
sudo grub-install --root-directory=/mnt --no-floppy \
	--modules="normal part_msdos ext2 multiboot" /dev/loop0
sudo umount /mnt/
sudo losetup -d /dev/loop1
sudo losetup -d /dev/loop0
