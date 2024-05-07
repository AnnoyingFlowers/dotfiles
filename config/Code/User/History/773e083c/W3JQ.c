#include <ctype.h>
#include <stdio.h>
#include <string.h>

void print_arguments(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        int len = strlen(argv[i]);
        for (int j = 0; j < len; j++) {
            char ch = argv[i][j];

            if (isalpha(ch) || isblank(ch)) {
                printf("'%c' == %d ", ch, ch);
            }
        }

        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    print_arguments(argc, argv);
    return 0;
}