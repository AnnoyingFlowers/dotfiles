#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int a = 0;
int choose(int n) {
    return rand() % n;
}
void foo(int depth) {
    if (a >= 65536) {
        printf("%d\n", depth);
        return;
    }
    switch (choose(3)) {
        case 0:
            a += 8;
            break;  // +8
        case 1:
            a += 4;
            foo(depth + 1);
            a += 4;
            break;  // +4+?+4
        default:
            foo(depth + 1);
            a += 4;
            foo(depth + 1);
            break;  // +?+4+?
    }
}

int main(int argc, char *argv[]) {
    int seed = time(0);
    srand(seed);
    int loop = 1;
    if (argc > 1) {
        sscanf(argv[1], "%d", &loop);
    }
    int i;
    for (i = 0; i < loop; i++) {
    haha:
        foo(0);
    }

    return 0;
}