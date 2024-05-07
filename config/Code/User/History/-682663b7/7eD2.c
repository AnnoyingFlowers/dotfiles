#include <assert.h>
#include <stdint.h>
#include <stdio.h>
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
    while (n) *a = c, n--, a++;
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
    while (n && *(unsigned char *)s1 == *(unsigned char *)s2) n--, s1++, s2++;
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

char *s[] = {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab",
             "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
             ", World!\n",
             "Hello, World!\n",
             "#####"};

char str1[] = "Hello";
char str[20] = "Hello, World!\n";

int main() {
    // check(strcmp(s[0], s[2]) == 0);
    // check(strcmp(s[0], s[1]) < 0);
    // check(strcmp(s[0] + 1, s[1] + 1) < 0);
    // check(strcmp(s[0] + 2, s[1] + 2) < 0);
    // check(strcmp(s[0] + 3, s[1] + 3) < 0);

    // assert(strcmp(strcat(strcpy(str, str1), s[3]), s[4]) == 0);
    memset(str, '#', 5);
    printf("%s\n", str);
    printf("%d\n", memcmp(str, s[5], 5));
    assert(memcmp(str, s[5], 5) == 0);

    return 0;
}
