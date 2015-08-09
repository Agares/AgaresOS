ASM = nasm
CC := ../local/bin/i686-elf-gcc
LD := ../local/bin/i686-elf-gcc

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
	-Wuninitialized -Werror

CFLAGS :=-Isrc -mno-sse -mno-sse2 -fno-asynchronous-unwind-tables -nostdlib -ffreestanding -std=c11 -Isrc $(WARNINGFLAGS)
LDFLAGS := -static -nostdlib -T ./$(SRCDIR)/linker.ld
ASMFLAGS := -felf32

.PHONY: all clean

all: $(DISTDIR)/boot/loader.bin

$(DISTDIR)/boot/loader.bin: $(OBJFILES)
	mkdir -p $(@D)
	$(LD) $(LDFLAGS) $(OBJFILES) -lgcc -o $@

$(OBJDIR)/%.a.o: $(SRCDIR)/%.asm
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r $(OBJDIR)
	rm -r $(DISTDIR)
