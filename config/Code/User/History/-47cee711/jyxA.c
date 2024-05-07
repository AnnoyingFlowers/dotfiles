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
    int src_offset, dest_offset, length;

    for (src_offset = 0; src_offset < N; src_offset++) {
        for (dest_offset = 0; dest_offset < N; dest_offset++) {
            for (length = 1; length <= N - max(src_offset, dest_offset);
                 length++) {
                reset();

                memmove(data + dest_offset, data + src_offset, length);

                if (dest_offset > src_offset) {
                    check_seq(0, src_offset, 1);
                    check_seq(src_offset, dest_offset - length + 1, 1);
                } else {
                    check_seq(0, dest_offset, 1);
                }

                if (src_offset < dest_offset) {
                    check_seq(dest_offset, dest_offset + length,
                              src_offset + 1);
                } else {
                    check_seq(dest_offset, dest_offset + length,
                              src_offset + 1);
                }

                if (dest_offset + length < N) {
                    if (src_offset + length <= dest_offset) {
                        check_seq(dest_offset + length, N,
                                  dest_offset + length + 1);
                    } else if (src_offset >= dest_offset) {
                        check_seq(
                            max(src_offset + length, dest_offset + length), N,
                            max(src_offset + length, dest_offset + length) + 1);
                    }
                }
            }
        }
    }
}

void write_test() {
    memset_test();
    strcpy_test();
    strncpy_test();
    strcat_test();
}