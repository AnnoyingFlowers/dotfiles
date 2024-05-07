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
    int i = 0;

    assert(memcmp(str1, str2, strlen(str1)) == correct[i++]);
    assert(memcmp(str1, str3, strlen(str1)) == correct[i++]);
    assert(memcmp(str1, str3, 5) == correct[i++]);
    assert(memcmp(str1, "", 0) == correct[i++]);
    assert(memcmp(str1, str3, strlen(str1) + 1) == correct[i++]);
    assert(memcmp("Hello", "Hell", 5) == correct[i++]);

    putch('y');
    putch('\n');
}

void strcmp_test() {
    int correct[] = {0, -30, -32, 32, 72};
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";
    char str3[] = "Hello World?";
    int i = 0;

    assert(strcmp(str1, str2) == correct[i++]);
    assert(strcmp(str1, str3) == correct[i++]);
    assert(strcmp("Hello", "Hello World!") == correct[i++]);
    assert(strcmp("Hello World!", "Hello") == correct[i++]);
    assert(strcmp(str1, "") == correct[i++]);

    putch('y');
    putch('\n');
}

void strncmp_test() {
    int correct[] = {0, 0, -30, 2, -4, 0, 72, -30, 0, 32};
    char str1[] = "Hello World!";
    char str2[] = "Hello World!";
    char str3[] = "Hello World?";
    char str4[] = "Hello Universe!";
    char str5[] = "Hi World!";
    int i = 0;

    assert(strncmp(str1, str2, strlen(str1)) == correct[i++]);
    assert(strncmp(str1, str2, 5) == correct[i++]);
    assert(strncmp(str1, str3, strlen(str1)) == correct[i++]);
    assert(strncmp(str1, str4, 7) == correct[i++]);
    assert(strncmp(str1, str5, strlen(str1)) == correct[i++]);
    assert(strncmp(str1, str2, 0) == correct[i++]);
    assert(strncmp(str1, "", 1) == correct[i++]);
    assert(strncmp(str1, str3, strlen(str1) + 5) == correct[i++]);
    assert(strncmp("Hello", "Hello World!", 5) == correct[i++]);
    assert(strncmp("Hello World!", "Hello", 14) == correct[i++]);

    putch('y');
    putch('\n');
}

void read_test() {
    strlen_test();
    memcmp_test();
    strcmp_test();
    strncmp_test();
}