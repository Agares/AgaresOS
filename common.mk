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
	-Wuninitialized -Wconversion -Werror

CFLAGS := -fno-asynchronous-unwind-tables -nostdlib -ffreestanding -std=c11 $(WARNINGFLAGS)
LDFLAGS := -static -L ./
ASMFLAGS := 
ASM = nasm

.DEFAULT_GOAL=all

clean:
	find $(OBJDIR) -not -name ".*" -type f -delete
	find $(DISTDIR) -not -name ".*" -type f -delete

$(OBJDIR)/%.a.o: $(SRCDIR)/%.asm
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
