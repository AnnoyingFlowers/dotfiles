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
    int32_t src1 = 0xaeb1c2aa;
    int32_t src2 = 0x4500ff2b;
    printf("%lx\n", ((int64_t)src1 * (int64_t)src2) >> 32);
    // 0x19d29ab9db1a18e4LL
    return 0;
}