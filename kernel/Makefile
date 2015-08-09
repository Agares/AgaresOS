ARCH := x86_64

-include ../common.mk
CC=../local/bin/x86_64-elf-gcc
LD=../local/bin/x86_64-elf-gcc

OBJFILES += $(patsubst src/%, obj/%, $(patsubst %.rs, %.rs.o, $(shell find $(SRCDIR) -type f -name "*.rs")))
LDFLAGS += -T ./$(SRCDIR)/linker.ld
CFLAGS += -m64 -mno-red-zone -Isrc -mcmodel=kernel
ASMFLAGS += -felf64
RUSTC := ../local/bin/rustc

all: $(DISTDIR)/boot/kernel.bin

$(OBJDIR)/%.rs.o: $(SRCDIR)/%.rs
	LD_LIBRARY_PATH=../local/lib $(RUSTC) -O --cfg arch_$(ARCH) --target=target.json $< -o $@

$(DISTDIR)/boot/kernel.bin: $(OBJFILES)
	mkdir -p $(@D)
	$(LD) $(LDFLAGS) $(OBJFILES) -o $@
