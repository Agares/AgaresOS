-include ../common.mk

LDFLAGS += -melf_i386  -T ./$(SRCDIR)/linker.ld
CFLAGS += -m32
ASMFLAGS +=  -felf32

.PHONY: all clean dist kernel.bin qemu

all: $(DISTDIR)/boot/loader.bin

$(DISTDIR)/boot/loader.bin: $(OBJFILES)
	$(LD) $(LDFLAGS) $(OBJFILES) -o $@
