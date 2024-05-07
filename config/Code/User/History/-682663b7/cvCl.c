#include <stdint.h>
#include <stdio.h>

char *strncpy(char *dst, const char *src, size_t n) {
    // size_t i;
    // for (i = 0; i < n && src[i] != '\0'; i++) dst[i] = src[i];
    // for (; i < n; i++) dst[i] = '\0';
    char *a = dst;
    while (n != 0 && (*a++ = *src++) != '\0') n--;
    if (n > 0)
        while (--n) *a++ = '1';
    return dst;
}
char *strcpy(char *dst, const char *src) {
    char *a = dst;
    while ((*a++ = *src++) != '\0')
        ;
    return dst;
}
int main() {
    char src[4] = "aaa";
    char dst[10] = "bbbbbbbbb";
    strcpy(dst, src);
    return 0;
}