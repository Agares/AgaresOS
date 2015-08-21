DISTDIR := dist
OBJDIR  := obj
SRCDIR  := src

CPPFILES = $(shell find $(SRCDIR) -type f -name "*.cpp")
CPPOBJFILES = $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(patsubst %.cpp, %.o, $(CPPFILES)))

ASMFILES = $(shell find $(SRCDIR) -type f -name "*.asm")
ASMOBJFILES = $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(patsubst %.asm, %.a.o, $(ASMFILES)))

OBJFILES := $(CPPOBJFILES) $(ASMOBJFILES)

CXXFLAGS := -Wall -Wextra -pedantic -Werror -mcmodel=kernel -I$(SRCDIR) -I$(SRCDIR)/arch/x86-64 -nostdlib -ffreestanding -std=c++14 -fno-rtti -fno-exceptions
LDFLAGS  := -static -nostdlib -T./$(SRCDIR)/linker.ld
ASMFLAGS := -felf64

ASM := nasm
CXX := ../local/bin/x86_64-elf-g++
LD  := ../local/bin/x86_64-elf-gcc

all: $(DISTDIR)/boot/kernel.bin

$(DISTDIR)/boot/kernel.bin: $(OBJFILES)
	mkdir -p $(@D)
	$(LD) $(LDFLAGS) $(OBJFILES) -lgcc -o $@

$(OBJDIR)/%.a.o: $(SRCDIR)/%.asm
	mkdir -p $(@D)
	$(ASM) $(ASMFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -r $(OBJDIR)
	rm -r $(DISTDIR)
