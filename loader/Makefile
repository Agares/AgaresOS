-include ../common.mk

LDFLAGS +=  -T ./$(SRCDIR)/linker.ld
.PHONY: all clean dist kernel.bin qemu

all: $(DISTDIR)/boot/loader.bin

$(DISTDIR)/boot/loader.bin: $(OBJFILES)
	$(LD) $(LDFLAGS) $(OBJFILES) -o $@

