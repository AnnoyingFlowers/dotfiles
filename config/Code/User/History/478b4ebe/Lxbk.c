#include <am.h>
#include <klib-macros.h>
#include <klib.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

#define INT_MIN -2147483648

int printf(const char *fmt, ...) {
    panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
    panic("Not implemented");
}

// 将int值转换为对应字符串，并放入str，最后把指向str的指针向后移字符串长度位
char *itoa(int num, char *str, int base) {
    int i = 0;
    int is_neg = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i++] = '\0';
        return str + i;
    }

    // 单独处理负数
    if (num == INT_MIN) {
        is_neg = 1;
        num = -(num / base);
        // 单独处理最后一位
        int rem = -(INT_MIN % base);
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    } else if (num < 0) {
        is_neg = 1;
        num = -num;
    }

    // 循环取最后一位
    while (num) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num /= base;
    }
    if (is_neg) str[i++] = '-';

    // reverse一下
    int l = 0, r = i - 1;
    while (l < r) {
        char tmp = str[l];
        str[l] = str[r];
        str[r] = tmp;
        l++, r--;
    }
    return str + i;
}

int sprintf(char *out, const char *fmt, ...) {
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
                break;
            case 'd':
                d = va_arg(ap, int);
                if (d == 0)
                    *str++ = '0';
                else
                    str = itoa(d, str, 10);
                break;
            case '%':
                *str++ = *fmt;
                break;
        }
    }
    *str = '\0';
    va_end(ap);
    return str - out;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
    panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
    panic("Not implemented");
}

#endif