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
    int32_t a = 0x01234567;
    int32_t b = 0x89abcdef;
    printf("%lx\n", ((int64_t)a * (int64_t)b) >> 32);
    return 0;
}