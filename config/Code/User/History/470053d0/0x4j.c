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
    int correct[] = {0, -30, 0, 0, -30, 111};
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";
    char str3[] = "Hello World?";
    assert(memcmp(str1, str2, strlen(str1)) == correct[0]);
    assert(memcmp(str1, str3, strlen(str1)) == correct[1]);
    assert(memcmp(str1, str3, 5) == correct[2]);
    assert(memcmp(str1, "", 0) == correct[3]);
    assert(memcmp(str1, str3, strlen(str1) + 1) == correct[4]);
    assert(memcmp("Hello", "Hell", 5) == correct[5]);
    putch('y');
    putch('\n');
}

void strcmp_test() {
    int correct[] = {0, -30, -32, 32, 72};
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";
    char str3[] = "Hello World?";

    assert(strcmp(str1, str2) == correct[0]);
    assert(strcmp(str1, str3) == correct[1]);
    assert(strcmp("Hello", "Hello World!") == correct[2]);
    assert(strcmp("Hello World!", "Hello") == correct[3]);
    assert(strcmp(str1, "") == correct[4]);

    putch('y');
    putch('\n');
}

void read_test() {
    strlen_test();
    memcmp_test();
    strcmp_test();
}