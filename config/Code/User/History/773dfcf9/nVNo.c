#include <stdio.h>

int main(int argc, char *argv[]) {
    // go through each string in argv

    int i = argc - 1;
    // C language does't have actual boolean type
    while (i >= 0) {
        printf("arg %d: %s\n", i, argv[i]);
        i--;
    }

    // let's make our own array of strings
    char *states[] = {"California", "Oregon", "Washington", "Texas"};

    int num_states = 4;
    i = num_states - 1;  // watch for this
    while (i >= 0) {
        printf("state %d: %s\n", i, states[i]);
        i--;
    }

    return 0;
}