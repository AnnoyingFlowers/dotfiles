#include <klibtest.h>

void strlen_test() {
    size_t correct[] = {0, 1, 3, 12, 21, 21, 18};
    char strs[][32] = {"",
                       "a",
                       "abc",
                       "Hello World!",
                       "Computer Science 101!",
                       "Line1\t\nLine2\t\nLine3\t\n",
                       "你好，世界！"};
    for (int i = 0; i < sizeof(correct) / sizeof(size_t); i++) {
        assert(correct[i] == strlen(strs[i]));
    }
    putch('y');
    putch('\n');
}

void memcmp_test() {
    int correct[] = {0, -30, 0, 0, -30, 1};
    char arr1[] = "Hello World!";
    char arr2[] = "Hello World!";
    char arr3[] = "Hello World?";
    for (int i = 0; i < sizeof(correct) / sizeof(int); i++) {
    }
}

void read_test() {
    strlen_test();
}