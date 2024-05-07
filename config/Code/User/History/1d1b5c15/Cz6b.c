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
    uint32_t a = 0x01234567;
    uint32_t b = 0x89abcdef;
    printf("%lx\n", ((uint64_t)a * (uint64_t)b));
    return 0;
}