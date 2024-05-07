#include <klibtest.h>
#include <limits.h>

void sprintf_test() {
    int data[] = {0,           INT_MAX / 17,  INT_MAX,      INT_MIN,
                  INT_MIN + 1, UINT_MAX / 17, INT_MAX / 17, UINT_MAX};
    char* correct10[] = {"0",           "126322567",   "2147483647",
                         "-2147483648", "-2147483647", "252645135",
                         "126322567",   "-1"};
    char* corrent16[] = {"0",        "7878787", "7fffffff", "80000000",
                         "80000001", "f0f0f0f", "7878787",  "ffffffff"};
    for (int i = 0; i < sizeof(data) / sizeof(int); i++) {
        char str[16];
        sprintf(str, "%x", data[i]);
        for (int j = 0; j < strlen(str); j++) {
            putch(str[j]);
        }
        putch('\n');
        assert(strcmp(str, correct10[i]) == 0);
    }

    putch('y');
    putch('\n');
}

void out_test() {
    sprintf_test();
}