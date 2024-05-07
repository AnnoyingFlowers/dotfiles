#include "trap.h"

int f0(int, int);
int f1(int, int);
int f2(int, int);
int f3(int, int);

int (*func[])(int, int) = {
    f0,
    f1,
    f2,
    f3,
};

int rec = 0, lvl = 0;

int f0(int n, int l) {
    if (l > lvl) lvl = l;
    rec++;
    return n <= 0 ? 1 : func[3](n / 3, l + 1);
};

int f1(int n, int l) {
    if (l > lvl) lvl = l;
    rec++;
    return n <= 0 ? 1 : func[0](n - 1, l + 1);
};

int f2(int n, int l) {
    if (l > lvl) lvl = l;
    rec++;
    return n <= 0 ? 1 : func[1](n, l + 1) + 9;
};

int f3(int n, int l) {
    if (l > lvl) lvl = l;
    rec++;
    return n <= 0 ? 1 : func[2](n / 2, l + 1) * 3 + func[2](n / 2, l + 1) * 2;
};

int ans[] = {38270, 218, 20};

int main() {
    /*
        解释一下为什么会出现不匹配的函数调用和返回：
            程序会按照f0 f3 f2 f1 f0 f3 f2 f1... 的顺序执行（不是call的顺序），
            但是f1 -> f0和f0 -> f3不是call，只是单纯的跳转（jalr zero, 0(a5)）
            导致除了第一次call f0，你找不到call f0或者是call f3，
            而且跳转时并没有把返回地址给ra，所以当有函数ret的时候，会根据ra直接跳转到上一次记录ra的地方
            所以ret f0之后会跳转到f2，ret f2之后到f3，ret f3之后到f2...
    */

    int x = func[0](14371, 0);
    check(x == ans[0]);    // answer
    check(rec == ans[1]);  // # recursions
    check(lvl == ans[2]);  // max depth
    return 0;
}
