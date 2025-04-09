#include <stdio.h>
#include <string.h>

void shell() {
    char command[128];
    while (1) {
        printf("SimpleOS> ");
        gets(command);

        if (strcmp(command, "ls") == 0) {
            printf("Mock ls command\n");
        } else if (strcmp(command, "cd") == 0) {
            printf("Mock cd command\n");
        } else if (strcmp(command, "touch") == 0) {
            printf("Mock touch command\n");
        } else if (strcmp(command, "rm") == 0) {
            printf("Mock rm command\n");
        } else if (strcmp(command, "my") == 0) {
            printf("Mock my command\n");
        } else {
            printf("Unknown command: %s\n", command);
        }
    }
}

void kernel_main() {
    printf("Welcome to Simple OS!\n");
    shell();
}
