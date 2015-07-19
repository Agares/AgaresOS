ARCH := x86_64

-include ../common.mk

OBJFILES += $(patsubst src/%, obj/%, $(patsubst %.rs, %.rs.o, $(shell find $(SRCDIR) -type f -name "*.rs")))
LDFLAGS += -melf_x86_64 -T ./$(SRCDIR)/linker.ld
CFLAGS += -m64 -mno-red-zone -Isrc -mcmodel=kernel
ASMFLAGS += -felf64
RUSTC := ../local/compiler/rustc/bin/rustc

all: $(DISTDIR)/boot/kernel.bin

$(OBJDIR)/%.rs.o: $(SRCDIR)/%.rs
	LD_LIBRARY_PATH=../local/compiler/rustc/lib $(RUSTC) -O --cfg arch_$(ARCH) --target=target.json $< -o $@

$(DISTDIR)/boot/kernel.bin: $(OBJFILES)
	mkdir -p $(@D)
	$(LD) $(LDFLAGS) $(OBJFILES) -o $@
