#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stddef.h>
#include <stdbool.h>

#define MAX_FILES 16
#define MAX_FILENAME_LEN 32

typedef enum {
    FILE_TYPE_FILE,
    FILE_TYPE_DIRECTORY
} FileType;

typedef struct File {
    char name[MAX_FILENAME_LEN];
    FileType type;
    bool used;
    struct File *parent;
    struct File *children[MAX_FILES];
} File;

void init_file_system();
void list_files();
void create_entry(const char *name, FileType type);
void delete_entry(const char *name);
void change_directory(const char *name);
File *find_child(const char *name);

#endif
