#include <stdio.h>

int main(int argc, char* argv[]) {
    // int puts(const char *s);
    // defined in <stdio.h>
    // puts() writes the string s and a trailing \n to stdout
    // return a nonnegative num on success, or EOF on error
    // other functions: fputc, fputs, putc, putchar, puts
    // putc(c, stdout) is equal to putchar(c)
    puts("Hello World.");
    puts("H");
    puts("e");
    puts("l");
    puts("l");
    puts("o");

    return 0;
}