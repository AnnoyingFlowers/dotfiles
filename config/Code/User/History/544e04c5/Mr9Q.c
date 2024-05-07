#include <klibtest.h>

void (*entry)() = NULL;  // mp entry

static const char *tests[256] = {
    ['H'] = "Usage: make run mainargs=*\n",
    ['w'] = "test write functions",
    ['r'] = "test read functions",
};

int main(const char *args) {
    switch (args[0]) {
        CASE('w', write_test);
        case 'H':
        default:
            for (int i = 0; i < 28; i++) {
                putch(tests['H'][i]);
            }
    }
    return 0;
}