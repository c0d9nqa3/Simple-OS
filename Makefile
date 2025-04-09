# Compiler and flags
CC = gcc
LD = ld
OBJCOPY = objcopy
CFLAGS = -m32 -ffreestanding -c
LDFLAGS = -m elf_i386 -T linker.ld
OBJCPYFLAGS = -O binary

# Source files
SOURCES = kernel.c utils.c file_system.c command_handler.c log.c keyboard.c test.c
HEADERS = utils.h file_system.h command_handler.h log.h keyboard.h
OBJECTS = kernel.o utils.o file_system.o command_handler.o log.o keyboard.o test.o

# Output files
KERNEL_ELF = kernel.elf
KERNEL_BIN = kernel.bin
BOOT_BIN = boot.bin
OS_IMG = os.img

# Default target
all: $(OS_IMG)

# Rule to generate the OS image
$(OS_IMG): $(BOOT_BIN) $(KERNEL_BIN)
	dd if=$(BOOT_BIN) of=$(OS_IMG) conv=notrunc
	dd if=$(KERNEL_BIN) of=$(OS_IMG) bs=512 seek=1 conv=notrunc

# Rule to generate the kernel binary
$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCOPY) $(OBJCPYFLAGS) $(KERNEL_ELF) $(KERNEL_BIN)

# Rule to generate the kernel ELF
$(KERNEL_ELF): $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $(KERNEL_ELF)

# Rule to compile each C file into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

# Clean target
clean:
	rm -f $(OBJECTS) $(KERNEL_ELF) $(KERNEL_BIN) $(OS_IMG)
