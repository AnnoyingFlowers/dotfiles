#include <stdarg.h>
#include <stdio.h>

int my_sprintf(char *out, const char *fmt, ...) {
    va_list ap;
    int d;
    // char c;
    char *s;

    va_start(ap, fmt);
    while (*fmt) {
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
    my_sprintf(out, "sssaaabbb%scccddd", "123");
    return 0;
}