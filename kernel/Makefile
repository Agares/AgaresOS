ARCH := x86_64

-include ../common.mk

LDFLAGS += -melf_x86_64 -T ./$(SRCDIR)/linker.ld
CFLAGS += -m64 -mno-red-zone
ASMFLAGS += -felf64

all: $(DISTDIR)/boot/kernel.bin

$(DISTDIR)/boot/kernel.bin: $(OBJFILES)
	mkdir -p $(@D)
	$(LD) $(LDFLAGS) $(OBJFILES) -o $@
