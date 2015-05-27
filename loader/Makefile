-include ../common.mk

LDFLAGS +=  -T ./$(SRCDIR)/linker.ld
.PHONY: all clean dist kernel.bin qemu

all: $(DISTDIR)/boot/kernel.bin

qemu: $(DISTDIR)/disk.img
	qemu-system-x86_64 -s $<

bochs: $(DISTDIR)/disk.img
	bochs

$(DISTDIR)/disk.img: $(DISTDIR)/boot/kernel.bin
	sudo ./tools/disk/image.sh

$(DISTDIR)/boot/kernel.bin: $(OBJFILES)
	$(LD) $(LDFLAGS) $(OBJFILES) -o $@

