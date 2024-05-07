#include <klibtest.h>

void (*entry)() = NULL;  // mp entry

static const char *tests[256] = {
    ['w'] = "write",
};

int main(int argc, const char *args[]) {
    switch (args[1][0]) {
        CASE('w', write);
        case 'H':
        default:
            printf("Usage: make run mainargs=*\n");
            for (int ch = 0; ch < 256; ch++) {
                if (tests[ch]) {
                    printf("  %c: %s\n", ch, tests[ch]);
                }
            }
    }
    return 0;
}