#include <ctype.h>
#include <stdio.h>
#include <string.h>

// forward declarations
void print_letters(char arg[]);

void print_arguments(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        int i = 0;

        for (i = 0; arg[i] != '\0'; i++) {
            char ch = arg[i];

            if (isalpha(ch) || isblank(ch)) {
                printf("'%c' == %d ", ch, ch);
            }
        }

        printf("\n");
    }
}

void print_letters(char arg[]) {
}

int main(int argc, char *argv[]) {
    print_arguments(argc, argv);
    return 0;
}