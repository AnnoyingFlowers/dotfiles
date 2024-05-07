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
    int32_t a = 0x80000000;
    uint64_t b = 0xffffffffffffffff;
    printf("%d\n", b == (uint64_t)SEXT(1, 1));
    return 0;
}