#include "log.h"

void execute_command(const char *command) {
    if (command[0] == '\0') {
        return;
    }

    // Log the command
    log_message(command);

    if (strcmp(command, "ls") == 0) {
        list_files();
    } else if (strncmp(command, "touch ", 6) == 0) {
        create_entry(command + 6, FILE_TYPE_FILE);
    } else if (strncmp(command, "mkdir ", 6) == 0) {
        create_entry(command + 6, FILE_TYPE_DIRECTORY);
    } else if (strncmp(command, "rm ", 3) == 0) {
        delete_entry(command + 3);
    } else if (strncmp(command, "cd ", 3) == 0) {
        change_directory(command + 3);
    } else if (strcmp(command, "logs") == 0) {
        display_logs();
    } else if (strcmp(command, "help") == 0) {
        print("Available commands: ls, touch <filename>, mkdir <dirname>, rm <name>, cd <dirname>, logs, help, exit\n");
    } else if (strcmp(command, "exit") == 0) {
        print("Exiting Shell...\n");
        while (1); // Infinite loop simulating exit
    } else {
        print("Unknown command: ");
        print(command);
        print("\n");
    }
}
