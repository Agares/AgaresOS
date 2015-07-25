ARCH := x86

-include ../common.mk

LDFLAGS += -T ./$(SRCDIR)/linker.ld
CFLAGS += -Isrc
ASMFLAGS +=  -felf32

.PHONY: all clean dist kernel.bin qemu

all: $(DISTDIR)/boot/loader.bin

$(DISTDIR)/boot/loader.bin: $(OBJFILES)
	mkdir -p $(@D)
	$(LD) $(LDFLAGS) $(OBJFILES) -lgcc -o $@
