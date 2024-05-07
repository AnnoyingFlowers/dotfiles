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
    char *a = dst;
    while ((*a++ = *src++) != '\0')
        ;
    return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
    // size_t i;
    // for (i = 0; i < n && src[i] != '\0'; i++) dst[i] = src[i];
    // for (; i < n; i++) dst[i] = '\0';
    char *a = dst;
    while (n != 0 && (*a++ = *src++) != '\0') n--;
    if (n > 0)
        while (--n) *a++ = '\0';
    return dst;
}

char *strcat(char *dst, const char *src) {
    char *a = dst;
    while (*a != '\0') a++;
    while ((*a++ = *src++) != '\0')
        ;
    return dst;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 == *s2 && *s1 != '\0') s1++, s2++;
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    if (!n--) return 0;
    while (*s1 == *s2 && *s1 != '\0' && n) s1++, s2++, n--;
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void *memset(void *s, int c, size_t n) {
    unsigned char *a = s;
    while (n) n--, *a++ = c;
    return s;
}

void *memmove(void *dst, const void *src, size_t n) {
    char *d = dst;
    const char *s = src;
    if (d == s) return dst;
    if (d < s)
        while (n--) *d++ = *s++;
    else
        while (n--) d[n] = s[n];
    return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
    char *o = out;
    const char *i = in;
    while (n--) *o++ = *i++;
    return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    if (n == 0) return 0;
    const unsigned char *l = s1, *r = s2;
    while (n && *l == *r) n--, l++, r++;
    return *l - *r;
}

#endif