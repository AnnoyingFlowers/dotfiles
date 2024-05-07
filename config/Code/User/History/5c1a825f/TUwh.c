#include <stdarg.h>
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
char *strcat(char *dst, const char *src) {
    char *a = dst;
    while (*a != '\0') a++;
    while ((*a++ = *src++) != '\0')
        ;
    return dst;
}
void itoa(int num, char *str, int base) {
    int i = 0;
    int is_neg = 0;
    if (num < 0) {
        is_neg = 1;
        num = -num;
    }
    while (num) {
        int rem = num % base;
        *str++ = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num /= base;
    }
    if (is_neg) *str = '-';
    int l = 0, r = str;
}
int my_sprintf(char *out, const char *fmt, ...) {
    va_list ap;
    int d;
    char *s;
    char *str = out;

    va_start(ap, fmt);
    for (; *fmt; fmt++) {
        if (*fmt != '%') {
            *str++ = *fmt;
            continue;
        }
        fmt++;
        switch (*fmt) {
            case 's':
                s = va_arg(ap, char *);
                strcpy(str, s);
                str += strlen(s);
                printf("%s\n%s\n", fmt, s);
                break;
            case 'd':
                d = va_arg(ap, int);
                printf("%s\n%d\n", fmt, d);
                if (d == 0)
                    *str++ = '0';
                else
                    itoa(d, str, 10);

                break;
            case '%':
                *str++ = *fmt;
                break;
        }
    }
    *str = '\0';
    va_end(ap);
    return 0;
}

int main() {
    char out[100];
    my_sprintf(out, "rrrr%%sssaaa%dbbb%scccddd", 123, "456", "789");
    printf("%s\n", out);
    printf("rrrr%%sssaaa%dbbb%scccddd", 123, "456");
    return 0;
}