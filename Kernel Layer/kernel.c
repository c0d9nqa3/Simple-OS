#include <stddef.h>

// Manual definition of boolean types
typedef _Bool bool;
#define true 1
#define false 0

#define VIDEO_MEMORY 0xb8000
#define MAX_CMD_LEN 128
#define MAX_FILES 16
#define MAX_FILENAME_LEN 32

typedef enum {
    FILE_TYPE_FILE,
    FILE_TYPE_DIRECTORY
} FileType;

// File structure
typedef struct {
    char name[MAX_FILENAME_LEN];
    FileType type;
    bool used;
} File;

// File system
File file_system[MAX_FILES];

// Function to initialize the file system
void init_file_system() {
    for (int i = 0; i < MAX_FILES; i++) {
        file_system[i].used = false;
    }
}

// Function to print a string to the screen
void print(const char *str) {
    volatile char *video = (volatile char *)VIDEO_MEMORY;
    while (*str) {
        *video++ = *str++;
        *video++ = 0x07; // White text, black background
    }
}

// Function to compare two strings
int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

// Function to copy a string
char *strcpy(char *dest, const char *src) {
    char *start = dest;
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return start;
}

// Function to compare the first n characters of two strings
int strncmp(const char *str1, const char *str2, size_t n) {
    while (n && *str1 && (*str1 == *str2)) {
        str1++;
        str2++;
        n--;
    }
    if (n == 0) {
        return 0;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

// Function to list files and directories
void list_files() {
    bool has_files = false;
    bool has_dirs = false;

    for (int i = 0; i < MAX_FILES; i++) {
        if (file_system[i].used && file_system[i].type == FILE_TYPE_DIRECTORY) {
            if (!has_dirs) {
                print("Directories:\n");
                has_dirs = true;
            }
            print(file_system[i].name);
            print("/\n");
        }
    }

    for (int i = 0; i < MAX_FILES; i++) {
        if (file_system[i].used && file_system[i].type == FILE_TYPE_FILE) {
            if (!has_files) {
                print("Files:\n");
                has_files = true;
            }
            print(file_system[i].name);
            print("\n");
        }
    }

    if (!has_files && !has_dirs) {
        print("No files or directories found.\n");
    }
}

// Function to create a file or directory
void create_entry(const char *name, FileType type) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (!file_system[i].used) {
            file_system[i].used = true;
            file_system[i].type = type;
            for (int j = 0; j < MAX_FILENAME_LEN; j++) {
                file_system[i].name[j] = name[j];
                if (name[j] == '\0') break;
            }
            if (type == FILE_TYPE_DIRECTORY) {
                print("Directory created: ");
            } else {
                print("File created: ");
            }
            print(name);
            print("\n");
            return;
        }
    }
    print("File system is full.\n");
}

// Function to delete a file or directory
void delete_entry(const char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (file_system[i].used && strcmp(file_system[i].name, name) == 0) {
            file_system[i].used = false;
            if (file_system[i].type == FILE_TYPE_DIRECTORY) {
                print("Directory deleted: ");
            } else {
                print("File deleted: ");
            }
            print(name);
            print("\n");
            return;
        }
    }
    print("File or directory not found: ");
    print(name);
    print("\n");
}

// Function to execute a command
void execute_command(const char *command) {
    if (command[0] == '\0') {
        return;
    }

    if (strcmp(command, "ls") == 0) {
        list_files();
    } else if (strncmp(command, "touch ", 6) == 0) {
        create_entry(command + 6, FILE_TYPE_FILE);
    } else if (strncmp(command, "mkdir ", 6) == 0) {
        create_entry(command + 6, FILE_TYPE_DIRECTORY);
    } else if (strncmp(command, "rm ", 3) == 0) {
        delete_entry(command + 3);
    } else if (strcmp(command, "help") == 0) {
        print("Available commands: ls, touch <filename>, mkdir <dirname>, rm <name>, help, exit\n");
    } else if (strcmp(command, "exit") == 0) {
        print("Exiting Shell...\n");
        while (1); // Infinite loop simulating exit
    } else {
        print("Unknown command: ");
        print(command);
        print("\n");
    }
}

// Simple shell implementation
void shell() {
    char command[MAX_CMD_LEN];
    while (1) {
        print("SimpleOS> ");

        // Simulated command input
        strcpy(command, "help"); // Replace with real input in the future

        execute_command(command);
    }
}

// Kernel entry point
void kernel_main() {
    print("Kernel is running!\n");

    // Initialize file system
    init_file_system();

    // Start shell
    shell();
}
