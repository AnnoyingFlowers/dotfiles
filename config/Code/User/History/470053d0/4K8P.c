#include <klibtest.h>

void strlen_test() {
    int correct[] = {0, 1, 3, 13, 21, 17, 18};
    char strs[][32] = {"",
                       "a",
                       "abc",
                       "Hello World!",
                       "Computer Science 101!",
                       "Line1\t\nLine2\t\nLine3\t\n",
                       "你好，世界！"};
    for (int i = 0; i < sizeof(correct) / sizeof(int); i++) {
        assert(correct[i] == strlen(strs[i]));
    }
}

void read_test() {
    strlen_test();
}