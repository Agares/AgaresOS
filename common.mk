COMMONDIR := ../common

SRCDIR := src
OBJDIR := obj
DISTDIR := dist

COMMONSRCDIR := $(COMMONDIR)/$(SRCDIR)
COMMONOBJDIR := $(COMMONDIR)/$(OBJDIR)/$(ARCH)

CFILES := $(shell find $(SRCDIR) -type f -name "*.c")
COBJFILES := $(patsubst src/%, obj/%, $(patsubst %.c, %.o, $(CFILES)))

ASMFILES := $(shell find $(SRCDIR) -type f -name "*.asm")
ASMOBJFILES := $(patsubst src/%, obj/%, $(patsubst %.asm, %.a.o, $(ASMFILES)))

COMMONCFILES := $(shell find $(COMMONSRCDIR) -type f -name "*.c")
COMMONCOBJFILES := $(patsubst $(COMMONSRCDIR)/%, $(COMMONOBJDIR)/%, $(patsubst %.c, %.o, $(COMMONCFILES)))

OBJFILES := $(COBJFILES) $(ASMOBJFILES) $(COMMONCOBJFILES)

WARNINGFLAGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
	-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
	-Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
	-Wuninitialized -Werror

CFLAGS := -fno-asynchronous-unwind-tables -nostdlib -ffreestanding -std=c11 $(WARNINGFLAGS)
LDFLAGS := -static -L ./
ASMFLAGS := 
ASM = nasm

.DEFAULT_GOAL=all

clean:
	find $(OBJDIR) -not -name ".*" -type f -delete
	find $(DISTDIR) -not -name ".*" -type f -delete

$(COMMONOBJDIR)/%.o: $(COMMONSRCDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.a.o: $(SRCDIR)/%.asm
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
