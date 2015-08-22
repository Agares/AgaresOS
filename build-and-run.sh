cd kernel
make dist/boot/kernel.bin
if [ $? -ne 0 ]; then
	echo 'Kernel build failed';
	exit 1;
fi
cd ../loader
make dist/boot/loader.bin
if [ $? -ne 0 ]; then
	echo 'Loader build failed';
	exit 1;
fi
cd ..

sudo ./tools/disk/image_update.sh

case $1 in
		bochs)
				bochs
				;;
		qemu)
				qemu-system-x86_64 -s dist/disk.img
esac
