cd kernel
make dist/boot/kernel.bin
cd ../loader
make dist/boot/loader.bin
cd ..

sudo ./tools/disk/image.sh

case $1 in
		bochs)
				bochs
				;;
		qemu)
				qemu-system-x86_64 -s dist/disk.img
esac
