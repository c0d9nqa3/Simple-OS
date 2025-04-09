#include "log.h"
#include "utils.h"

#define MAX_LOGS 100

char logs[MAX_LOGS][128];
int log_index = 0;

// Function to log a message
void log_message(const char *message) {
    if (log_index < MAX_LOGS) {
        strcpy(logs[log_index++], message);
    } else {
        print("Log capacity reached. No more logs can be added.\n");
    }
}

// Function to display all logs
void display_logs() {
    print("System Logs:\n");
    for (int i = 0; i < log_index; i++) {
        print(logs[i]);
        print("\n");
    }
}
