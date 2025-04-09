#include <stdio.h>
#include <string.h>

#define DISK_SIZE 1024 * 1024 // 1MB

int main() {
    FILE *disk = fopen("disk.img", "wb");
    if (!disk) {
        perror("Failed to create disk image");
        return 1;
    }
    char empty[DISK_SIZE];
    memset(empty, 0, DISK_SIZE);
    fwrite(empty, DISK_SIZE, 1, disk);
    fclose(disk);
    printf("Created empty disk image\n");
    return 0;
}
