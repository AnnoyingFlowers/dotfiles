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
    assert(memcmp(arr1, arr2, strlen(arr1)) == correct[0]);
    assert(memcmp(arr1, arr3, strlen(arr1)) == correct[1]);
    assert(memcmp(arr1, arr3, 5) == correct[2]);
    assert(memcmp(arr1, "", 0) == correct[3]);
    assert(memcmp(arr1, arr3, strlen(arr1) + 1) == correct[4]);
    assert(memcmp("Hello", "Hell", 5) == correct[5]);
    putch('y');
    putch('\n');
}
}

void read_test() {
    strlen_test();
}