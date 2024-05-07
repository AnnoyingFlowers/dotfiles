#include <stdarg.h>
#include <stdio.h>

int my_sprintf(char *out, const char *fmt, ...) {
    va_list ap;
    int d;
    char *s;

    va_start(ap, fmt);
    while (*fmt) {
        if (*fmt++ != '%') continue;
        switch (*fmt++) {
            case 's':
                s = va_arg(ap, char *);
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
    my_sprintf(out, "%sssaaabbb%scccddd", "123", "456", "789");
    return 0;
}