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
    uint32_t b = 0xffffffff;
    printf("%d\n", b == (uint32_t)SEXT(1, 1));
    return 0;
}