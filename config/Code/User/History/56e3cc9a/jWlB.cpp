#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "verilated.h"
// Include model header, generated from Verilating "top.v"
#include "Vtop.h"
int main(int argc, char** argv) {
    Vtop* top = new Vtop{contextp};
    while (1) {
        int a = rand() & 1;
        int b = rand() & 1;
        top->a = a;
        top->b = b;
        top->eval();
        printf("a = %d, b = %d, f = %d\n", a, b, top->f);
        assert(top->f == (a ^ b));
    }
    top->final();
    delete top;
    return 0;
}
