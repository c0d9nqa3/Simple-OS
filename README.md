# Simple-OS

Simple-OS is a lightweight operating system developed from scratch, designed to demonstrate core OS concepts such as memory layout, I/O handling, and command execution. It features a custom bootloader, a basic kernel, keyboard input handling, a simple file system, and a shell with user command support. The system is designed to run from a disk image.

## Features

- **Custom Bootloader**: Initializes the system and loads the kernel into memory.
- **Basic Kernel**: Manages core functionalities and system resources.
- **Keyboard Input Handling**: Captures and processes user input from the keyboard.
- **Simple File System**: Provides basic file management capabilities.
- **Shell with Command Support**: Allows users to execute commands and interact with the system.

## Project Structure

Simple-OS/ ├── Bootloader/ # Bootloader source code and binaries ├── Kernel Layer/ # Kernel source code and related files ├── Device Drivers/ # Drivers for hardware components (e.g., keyboard) ├── FileSystem Layer/ # Implementation of the simple file system ├── Command Interface/ # Shell and command handling modules ├── Utility Layer/ # Utility functions and helper modules ├── Makefile # Build script for compiling the OS └── README.md # Project documentation

## Getting Started

Follow the steps below to build and run Simple-OS locally.

### 1. Clone the Repository

\`\`\`bash
git clone https://github.com/c0d9nqa3/Simple-OS.git
\`\`\`

### 2. Navigate to the Project Directory

\`\`\`bash
cd Simple-OS
\`\`\`

### 3. Build the OS

Make sure you have \`make\`, \`nasm\`, and a suitable compiler installed.

\`\`\`bash
make
\`\`\`

This will compile the bootloader, kernel, and all related modules into a bootable disk image.

### 4. Run the OS in an Emulator

Use [QEMU](https://www.qemu.org/) or a similar x86 emulator:

\`\`\`bash
make run
\`\`\`

This launches QEMU with the generated disk image and starts the operating system.

---

> 💡 **Note**:  
> If \`make run\` doesn't work, ensure QEMU is installed and available in your system path.  
>
> **macOS (Homebrew):**
> \`\`\`bash
> brew install qemu
> \`\`\`
>
> **Ubuntu/Debian:**
> \`\`\`bash
> sudo apt install qemu
> \`\`\`

### 5. Clean Build Files (Optional)

To clean all compiled binaries and temporary files:

\`\`\`bash
make clean
\`\`\`
