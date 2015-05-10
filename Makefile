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

CFLAGS := -fno-asynchronous-unwind-tables -m32 -nostdlib -nostdinc -ffreestanding -std=c11 $(WARNINGFLAGS)
LDFLAGS := -melf_i386 -static -L ./ -T ./$(SRCDIR)/linker.ld
ASMFLAGS :=  -felf32
ASM = nasm

.PHONY: all clean dist kernel.bin qemu

all: directories $(DISTDIR)/kernel.bin

clean:
	rm -rf **/*.o **/*.d kernel.bin

$(DISTDIR)/kernel.bin: $(OBJFILES)
	$(LD) $(LDFLAGS) $(OBJFILES) -o $@

$(OBJDIR)/%.a.o: $(SRCDIR)/%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

directories: 
	mkdir -p $(OBJDIR) $(DISTDIR)


