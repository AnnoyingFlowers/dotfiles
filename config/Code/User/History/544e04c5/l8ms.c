#include <klibtest.h>

void (*entry)() = NULL;  // mp entry

static const char *tests[256] = {
    ['H'] = "display this help message",
    ['w'] = "write_function_test",
};

int main(const char *args) {
    switch (args[0]) {
        CASE('w', write_test);
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