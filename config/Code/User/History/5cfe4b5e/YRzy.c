#include <klibtest.h>
#include <limits.h>

void sprintf_test() {
    int data[] = {0,           INT_MAX / 17,  INT_MAX,      INT_MIN,
                  INT_MIN + 1, UINT_MAX / 17, INT_MAX / 17, UINT_MAX};
    for (int i = 0; i < sizeof(data) / sizeof(int); i++) {
        printf("%d, ", data[i]);
    }
}

void read_test() {
    sprintf_test();
}