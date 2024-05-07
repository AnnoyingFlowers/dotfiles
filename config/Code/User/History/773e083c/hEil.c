#include <ctype.h>
#include <stdio.h>
#include <string.h>

void print_arguments(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        int len = strlen(argv[i]);
        for (int j = 0; j < len; j++) {
            char ch = argv[i][j];
            /*
            int isalnum(int c);
            int isalpha(int c);
            int iscntrl(int c);
            int isdigit(int c);
            int isgraph(int c);
            int islower(int c);
            int isprint(int c);
            int ispunct(int c);
            int isspace(int c);
            int isupper(int c);
            int isxdigit(int c);

            int isascii(int c);
            int isblank(int c);
            */
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