#include <klibtest.h>

void (*entry)() = NULL;  // mp entry

static const char *tests[256] = {
    ['H'] = "Usage: make run mainargs=*\n",
    ['w'] = "write_function_test",
};

int main(const char *args) {
    switch (args[0]) {
        CASE('w', write_test);
        case 'H':
        default:
            for (int i = 0; i < 28; i++) {
                putch() printf();
            }
    }
    return 0;
}