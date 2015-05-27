This is a simple operating system, which aims to be a microkernel. At the moment it only supports x86 processors.

## Architecture
### The 32-bit loader (which is loaded into memory by multiboot2 compliant bootloader)
Responsible for setting up GDT and loading the kernel (which is in ELF format), that is put into memory by the bootloader.
### The 64-bit kernel (to be done)
