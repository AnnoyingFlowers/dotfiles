#include <stdio.h>

int main() {
    int age = 10;
    int height = 72;

    // man 3 printf
    // %<conversion>
    // d, i - int
    // o, u, x, X - unsigned int
    // e, E, f, F, g, G, a, A - double
    // c - char
    // s - const char*
    printf("I am %d years old.\n", age);
    printf("I am %d inches tall.\n", height);

    return 0;
}