#include "keyboard.h"
#include "utils.h"

void simulate_keyboard_input(char *buffer) {
    print("Simulated Input> ");
    strcpy(buffer, "mkdir test_dir"); // Replace this with dynamic or test input
    print(buffer);
    print("\n");
}
