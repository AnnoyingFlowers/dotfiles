#include <klibtest.h>
#include <limits.h>

void sprintf_test() {
    int data[] = {0,           INT_MAX / 17,  INT_MAX,      INT_MIN,
                  INT_MIN + 1, UINT_MAX / 17, INT_MAX / 17, UINT_MAX};
    // char* correct[] = {"0",           "126322567", "2147483647",
    // "-2147483648",
    //    "-2147483647", "252645135", "126322567",  "-1"};
    for (int i = 0; i < sizeof(data) / sizeof(int); i++) {
        char str[16];
        sprintf(str, "%x", data[i]);
        for (int j = 0; j < strlen(str); j++) {
            putch(str[j]);
        }
        putch('\n');
        // assert(strcmp(str, correct[i]) == 0);
    }

    putch('y');
    putch('\n');
}

void out_test() {
    sprintf_test();
}