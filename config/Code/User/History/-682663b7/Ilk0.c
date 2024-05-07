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
int strncmp(const char *s1, const char *s2, size_t n) {
    if (!n--) return 0;
    while (*s1 == *s2 && *s1 != '\0' && n) s1++, s2++, n--;
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}
int main() {
    char src[10] = "abcd";
    char dst[10] = "abc";
    printf("%d\n", strncmp(dst, src, 3));
    return 0;
}