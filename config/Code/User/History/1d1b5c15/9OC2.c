#include <stdint.h>
#include <stdio.h>
#define SEXT(x, len)         \
    ({                       \
        struct {             \
            int64_t n : len; \
        } __x = {.n = x};    \
        (uint64_t) __x.n;    \
    })
int main() {
    int64_t a = 0x0123456789abcdef;
    int64_t b = 0x0123456789abcdef;
    printf("%lx\n", ((uint64_t)a * (uint64_t)b) >> 64);
    return 0;
}