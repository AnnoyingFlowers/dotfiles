#include <stdint.h>
#include <stdio.h>
#define SEXT(x, len)            \
    ({                          \
        struct {                \
            __int128_t n : len; \
        } __x = {.n = x};       \
        (__uint128_t) __x.n;    \
    })
int main() {
    uint64_t src1 = 0x19d29ab9db1a18e4;
    uint64_t src2 = 0x19d29ab9db1a18e4;
    uint64_t rd = ((SEXT(src1, 64) * SEXT(src2, 64)) >> 64);
    printf("%llx\n", SEXT(src1, 64));
    printf("%llx\n", SEXT(src2, 64));
    printf("%lx\n", rd);
    rd = (int64_t)src1 * (int64_t)src2;
    printf("%lx\n", rd);
    // 0x19d29ab9db1a18e4LL
    return 0;
}