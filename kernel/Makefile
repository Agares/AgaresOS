-include ../common.mk

LDFLAGS += -T ./$(SRCDIR)/linker.ld

$(DISTDIR)/boot/kernel.bin: $(OBJFILES)
	mkdir -p $(@D)
	$(LD) $(LDFLAGS) $(OBJFILES) -o $@
