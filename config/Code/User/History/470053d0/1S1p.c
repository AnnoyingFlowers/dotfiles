#include <klibtest.h>

void strlen_test() {
    int correct[] = {0, 1, 3, 13, 21, 17, 18};
    char strs[][32] = {"",
                       "a",
                       "abc",
                       "Hello World!",
                       "Computer Science 101!",
                       "Line1\nLine2\nLine3",
                       "你好，世界！"};
}

void read_test() {
    strlen_test();
}