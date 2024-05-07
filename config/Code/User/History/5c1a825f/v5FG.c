#include <stdarg.h>
#include <stdio.h>

char *strcpy(char *dst, const char *src) {
    char *a = dst;
    while ((*a++ = *src++) != '\0')
        ;
    return dst;
}

int my_sprintf(char *out, const char *fmt, ...) {
    va_list ap;
    int d;
    char *s;
    char *str = out;

    va_start(ap, fmt);
    while (*fmt) {
        if (*fmt != '%') {
            *str++ = *fmt++;
            continue;
        }
        switch (*++fmt) {
            case 's':
                s = va_arg(ap, char *);
                strcpy(str, s);
                printf("%s\n%s\n", fmt, s);
                break;
            case 'd':
                d = va_arg(ap, int);
                printf("%s\n%d\n", fmt, d);
                break;
        }
    }
    va_end(ap);
    return 0;
}

int main() {
    char out[100];
    my_sprintf(out, "rrrr%sssaaabbb%scccddd", "123", "456", "789");
    printf("%s\n", out);
    return 0;
}