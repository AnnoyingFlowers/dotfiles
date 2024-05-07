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
    int32_t b = 2;
    printf("%lx\n", a >> 32);
    return 0;
}