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
    uint32_t a = -1;
    int64_t b = 0x0123456789abcdef;
    printf("%x\n", a);
    return 0;
}