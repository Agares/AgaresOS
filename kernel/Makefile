-include ../common.mk

LDFLAGS += -T ./$(SRCDIR)/linker.ld

$(DISTDIR)/boot/kernel.bin: $(OBJFILES)
	$(LD) $(LDFLAGS) $(OBJFILES) -o $@
