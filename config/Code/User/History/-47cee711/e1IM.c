#include <klibtest.h>

#define N 32
uint8_t data[N];

void reset() {
    int i;
    for (i = 0; i < N; i++) {
        data[i] = i + 1;
    }
}

// 检查[l,r)区间中的值是否依次为val, val + 1, val + 2...
void check_seq(int l, int r, int val) {
    int i;
    for (i = l; i < r; i++) {
        assert(data[i] == val + i - l);
    }
}

// 检查[l,r)区间中的值是否均为val
void check_eq(int l, int r, int val) {
    int i;
    for (i = l; i < r; i++) {
        assert(data[i] == val);
    }
}

void memset_test() {
    int l, r;
    for (l = 0; l < N; l++) {
        for (r = l + 1; r <= N; r++) {
            reset();
            uint8_t val = (l + r) / 2;
            memset(data + l, val, r - l);
            check_seq(0, l, 1);
            check_eq(l, r, val);
            check_seq(r, N, r + 1);
        }
    }
    putch('y');
    putch('\n');
}

void strcpy_test() {
    char src[N / 2];
    for (int i = 0; i < N / 2 - 1; i++) {
        src[i] = 'A' + i;
    }
    src[N / 2 - 1] = '\0';

    for (int offset = 0; offset < N - N / 2; offset++) {
        reset();
        strcpy((char*)data + offset, src);
        check_seq(0, offset, 1);
        check_seq(offset, offset + N / 2 - 1, 'A');
        check_eq(offset + N / 2 - 1, offset + N / 2, '\0');
        check_seq(offset + N / 2, N, offset + N / 2 + 1);
    }
    putch('y');
    putch('\n');
}

void strncpy_test() {
    char src[N / 2];
    for (int i = 0; i < N / 2 - 1; i++) {
        src[i] = 'A' + i;
    }
    src[N / 2 - 1] = '\0';

    for (int offset = 0; offset < N / 4; offset++) {
        for (int n = 0; n < N * 3 / 4; n++) {
            reset();
            strncpy((char*)data + offset, src, n);

            check_seq(0, offset, 1);
            if (n < N / 2) {
                check_seq(offset, offset + n, 'A');
            } else {
                check_seq(offset, offset + N / 2 - 1, 'A');
                check_eq(offset + N / 2 - 1, offset + n, '\0');
            }
            check_seq(offset + n, N, offset + n + 1);
        }
    }
    putch('y');
    putch('\n');
}

void strcat_test() {
    char src[N / 2];
    for (int i = 0; i < N / 2 - 1; i++) {
        src[i] = 'A' + i;
    }
    src[N / 2 - 1] = '\0';

    for (int offset = 0; offset < N - N / 2; offset++) {
        reset();
        data[offset] = '\0';
        strcat((char*)data, src);

        check_seq(0, offset, 1);
        check_seq(offset, offset + N / 2 - 1, 'A');
        check_seq(offset + N / 2 - 1, offset + N / 2, '\0');
    }
    putch('y');
    putch('\n');
}

void memmove_test() {
    int src_off, dest_off, len;

    for (src_off = 0; src_off < N; src_off++) {
        for (dest_off = 0; dest_off < N; dest_off++) {
            for (len = 1; len <= N - MAX(src_off, dest_off); len++) {
                reset();

                memmove(data + dest_off, data + src_off, len);

                if (src_off < dest_off) {
                    check_seq(0, src_off, 1);
                    check_seq(src_off, dest_off - len, src_off + 1);
                } else {
                    check_seq(0, dest_off, 1);
                }

                check_seq(dest_off, dest_off + len, src_off + 1);

                if (dest_off + len < N) {
                    if (src_off + len <= dest_off) {
                        check_seq(dest_off + len, N, dest_off + len + 1);
                    } else if (dest_off <= src_off) {
                        check_seq(src_off + len, N, src_off + len + 1);
                    }
                }
            }
        }
    }
    putch('y');
    putch('\n');
}

void memcpy_test() {
    uint8_t src[N];
    for (int i = 0; i < N; i++) {
        src[i] = N - i;
    }

    for (int offset = 0; offset <= N / 2; offset++) {
        for (int len = 1; len <= N - offset; len++) {
            reset();  // 每次循环前重置data数组
            memcpy(data + offset, src,
                   len);  // 将src的前len个元素复制到data的offset位置

            // 检查复制区间的左侧
            check_seq(0, offset, 1);
            // 检查复制区间本身
            for (int i = offset; i < offset + len; i++) {
                assert(
                    data[i] ==
                    N - (i -
                         offset));  // 检查复制区间是否正确复制了src的前len个元素
            }
            // 检查复制区间的右侧
            if (offset + len < N) {
                check_seq(offset + len, N, offset + len + 1);
            }
        }
    }
}

void write_test() {
    memset_test();
    strcpy_test();
    strncpy_test();
    strcat_test();
    memmove_test();
}