SRCDIR := src
OBJDIR := obj
DISTDIR := dist

CFILES := $(shell find $(SRCDIR) -type f -name "*.c")
COBJFILES := $(patsubst src/%, obj/%, $(patsubst %.c, %.o, $(CFILES)))

ASMFILES := $(shell find $(SRCDIR) -type f -name "*.asm")
ASMOBJFILES := $(patsubst src/%, obj/%, $(patsubst %.asm, %.a.o, $(ASMFILES)))

OBJFILES := $(COBJFILES) $(ASMOBJFILES)

WARNINGFLAGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
	-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
	-Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
	-Wuninitialized -Wconversion -Wstrict-prototypes

CFLAGS := -fno-asynchronous-unwind-tables -m32 -nostdlib -ffreestanding -std=c11 $(WARNINGFLAGS)
LDFLAGS := -melf_i386 -static -L ./ -T ./$(SRCDIR)/linker.ld
ASMFLAGS := -felf32
ASM = nasm

.PHONY: all clean dist kernel.bin qemu

all: $(DISTDIR)/boot/kernel.bin

qemu: $(DISTDIR)/disk.img
	qemu-system-x86_64 $<

clean:
	find $(OBJDIR) -not -name ".*" -type f -delete
	find $(DISTDIR) -not -name ".*" -type f -delete

$(DISTDIR)/disk.img: $(DISTDIR)/boot/kernel.bin
	sudo ./tools/disk/image.sh

$(DISTDIR)/boot/kernel.bin: $(OBJFILES)
	$(LD) $(LDFLAGS) $(OBJFILES) -o $@

$(OBJDIR)/%.a.o: $(SRCDIR)/%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@
