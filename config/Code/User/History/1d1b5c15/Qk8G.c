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
    uint32_t src1 = 0xaeb1c2aa;
    uint32_t src2 = 0xaeb1c2aa;
    uint32_t rd = ((SEXT(src1, 32) * SEXT(src2, 32)) >> 32);
    printf("%lx\n", SEXT(src1, 32));
    printf("%lx\n", SEXT(src2, 32));
    printf("%x\n", rd);
    rd = (int32_t)src1 * (int32_t)src2;
    printf("%x\n", rd);
    // 0x19d29ab9db1a18e4LL
    return 0;
}