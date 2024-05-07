#include <stdio.h>

int main(int argc, char *argv[]) {
    int distance = 100;
    float power = 2.345f;
    double super_power = 56789.4532;
    char initial = 'A';
    char first_name[] = "Zed";
    char last_name[] = "Shaw";
    /*
    a, A    以十六进制形式输出浮点数(C99 新增)。
        实例 printf("pi=%a\n", 3.14); 输出 pi=0x1.91eb86p+1。
    d	    以十进制形式输出带符号整数(正数不输出符号)
    o	    以八进制形式输出无符号整数(不输出前缀0)
    x,X	    以十六进制形式输出无符号整数(不输出前缀Ox)
    u	    以十进制形式输出无符号整数
    f   	以小数形式输出单、双精度实数
    e,E	    以指数形式输出单、双精度实数
    g,G	    以%f或%e中较短的输出宽度输出单、双精度实数
    c	    输出单个字符
    s	    输出字符串
    p	    输出指针地址
    lu	    32位无符号整数
    llu	    64位无符号整数
    */
    printf("You are %d miles away.\n", distance);
    printf("You have %f levels of power.\n", power);
    printf("You have %f awesome super powers.\n", super_power);
    printf("I have an initial %c.\n", initial);
    printf("I have a first name %s.\n", first_name);
    printf("I have a last name %s.\n", last_name);
    printf("My whole name is %s %c. %s.\n", first_name, initial, last_name);

    return 0;
}