// Valgrind is in essence a virtual machine using just-in-time
// compilation techniques, including dynamic recompilation.
// Nothing from the original program ever gets run directly
// on the host processor.
#include <stdio.h>

/* Warning: This program is wrong on purpose. */

int main() {
    int age = 10;
    int height;

    printf("I am %d years old.\n");
    printf("I am %d inches tall.\n", height);

    return 0;
}