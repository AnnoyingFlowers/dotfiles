#include <klibtest.h>

void strlen_test() {
    int correct[] = {0, 1, 3, 12, 21, 21, 18};
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
    putch('y');
    putch('\n');
}

void memcmp_test() {
    char arr1[] = "Hello World!";
    char arr2[] = "Hello World!";
    char arr3[] = "Hello World?";
    int result;

    result = memcmp(arr1, arr2, strlen(arr1));
    assert(result == 0);

    result = memcmp(arr1, arr3, strlen(arr1));
    assert(result != 0);

    result = memcmp(arr1, arr3, 5);
    assert(result == 0);

    result = memcmp(arr1, "", 0);
    assert(result == 0);

    result = memcmp(arr1, arr3, strlen(arr1) + 1);
    assert(result != 0);

    result = memcmp("Hello", "Hell", 5);
    assert(result > 0);
}

void read_test() {
    strlen_test();
}