#include "utils.h"

#define VIDEO_MEMORY 0xb8000

void print(const char *str) {
    volatile char *video = (volatile char *)VIDEO_MEMORY;
    while (*str) {
        *video++ = *str++;
        *video++ = 0x07; // White text, black background
    }
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

char *strcpy(char *dest, const char *src) {
    char *start = dest;
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return start;
}

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
