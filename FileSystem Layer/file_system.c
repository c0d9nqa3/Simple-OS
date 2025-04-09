#include "file_system.h"
#include "utils.h"

File root_directory;
File *current_directory;

void init_file_system() {
    root_directory.used = true;
    root_directory.type = FILE_TYPE_DIRECTORY;
    root_directory.parent = NULL;
    for (int i = 0; i < MAX_FILES; i++) {
        root_directory.children[i] = NULL;
    }
    strcpy(root_directory.name, "/");
    current_directory = &root_directory;
}

void list_files() {
    print("Current Directory: ");
    print(current_directory->name);
    print("\n");

    bool has_content = false;

    for (int i = 0; i < MAX_FILES; i++) {
        if (current_directory->children[i]) {
            has_content = true;
            if (current_directory->children[i]->type == FILE_TYPE_DIRECTORY) {
                print("[DIR] ");
            }
            print(current_directory->children[i]->name);
            print("\n");
        }
    }

    if (!has_content) {
        print("No files or directories found.\n");
    }
}

void create_entry(const char *name, FileType type) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (current_directory->children[i] == NULL) {
            File *new_entry = (File *)malloc(sizeof(File));
            new_entry->used = true;
            new_entry->type = type;
            new_entry->parent = current_directory;
            for (int j = 0; j < MAX_FILES; j++) {
                new_entry->children[j] = NULL;
            }
            strcpy(new_entry->name, name);
            current_directory->children[i] = new_entry;

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
    print("Directory is full.\n");
}

void delete_entry(const char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (current_directory->children[i] && strcmp(current_directory->children[i]->name, name) == 0) {
            free(current_directory->children[i]);
            current_directory->children[i] = NULL;
            print("Deleted: ");
            print(name);
            print("\n");
            return;
        }
    }
    print("File or directory not found: ");
    print(name);
    print("\n");
}

void change_directory(const char *name) {
    if (strcmp(name, "..") == 0) {
        if (current_directory->parent != NULL) {
            current_directory = current_directory->parent;
            print("Moved to parent directory.\n");
        } else {
            print("Already in root directory.\n");
        }
    } else {
        File *target = find_child(name);
        if (target && target->type == FILE_TYPE_DIRECTORY) {
            current_directory = target;
            print("Changed directory to: ");
            print(name);
            print("\n");
        } else {
            print("Directory not found: ");
            print(name);
            print("\n");
        }
    }
}

File *find_child(const char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (current_directory->children[i] && strcmp(current_directory->children[i]->name, name) == 0) {
            return current_directory->children[i];
        }
    }
    return NULL;
}
