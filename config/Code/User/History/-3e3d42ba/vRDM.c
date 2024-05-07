#include <klib-macros.h>
#include <klib.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
    const char *a = s;
    while (*a++ != '\0')
        ;
    return (size_t)(a - s - 1);
}

char *strcpy(char *dst, const char *src) {
    while (*src != '\0') *dst = *src++;
    return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
    panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
    panic("Not implemented");
}

int strcmp(const char *s1, const char *s2) {
    panic("Not implemented");
}

int strncmp(const char *s1, const char *s2, size_t n) {
    panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
    panic("Not implemented");
}

void *memmove(void *dst, const void *src, size_t n) {
    panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
    panic("Not implemented");
}

int memcmp(const void *s1, const void *s2, size_t n) {
    panic("Not implemented");
}

#endif