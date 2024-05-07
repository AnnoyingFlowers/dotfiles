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
            for (int i = 0; i < 28; i++) {
                printf("Usage: make run mainargs=*\n");
            }
    }
    return 0;
}