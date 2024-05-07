#include <stdio.h>
char full_name[] = {'Z', 'e', 'd', ' ', 'A', '.', ' ', 'S', 'h', 'a', 'w'};
int main(int argc, char *argv[]) {
    char name[] = "Zed";
    int areas[] = {10, 12, 13, 14, 20};

    // WARNING: On some systems you may have to change the
    // %ld in this code to a %u since it will use unsigned ints
    printf("The size of an int: %ld\n", sizeof(int));
    printf("The size of areas (int[]): %ld\n", sizeof(areas));
    printf("The number of ints in areas: %ld\n", sizeof(areas) / sizeof(int));
    // 很奇怪，我的valgrind不会检测出数组访问越界
    printf("The first area is %d, the 2nd %d.\n", areas[100], areas[1]);

    printf("The size of a char: %ld\n", sizeof(char));
    printf("The size of name (char[]): %ld\n", sizeof(name));
    printf("The number of chars: %ld\n", sizeof(name) / sizeof(char));

    printf("The size of full_name (char[]): %ld\n", sizeof(full_name));
    printf("The number of chars: %ld\n", sizeof(full_name) / sizeof(char));

    // 字符串没加\0也能正常跑
    printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);

    return 0;
}