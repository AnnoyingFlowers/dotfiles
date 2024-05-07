#include <stdio.h>
#include <string.h>

int main() {
    char arr1[] = "Hello World!";
    char arr2[] = "Hello World!";
    char arr3[] = "Hello World?";

    printf("%d", memcmp(arr1, arr2, strlen(arr1)));

    assert(memcmp(arr1, arr3, strlen(arr1)) != 0);

    assert(memcmp(arr1, arr3, 5) == 0);

    assert(memcmp(arr1, "", 0) == 0);

    assert(memcmp(arr1, arr3, strlen(arr1) + 1) != 0);

    assert(memcmp("Hello", "Hell", 5) > 0);
    for (int i = 0; i < sizeof(correct) / sizeof(int); i++) {
        printf("%ld, ", strlen(strs[i]));
    }

    return 0;
}