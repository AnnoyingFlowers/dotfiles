#include <cstdint>

#include "Vour__Dpi.h"
#include "Vtop.h"
#include "paddr.h"
#include "svdpi.h"
#include "verilated.h"
#include "verilated_fst_c.h"

Vtop *top = NULL;
VerilatedContext *contextp = NULL;
VerilatedFstC *tfp = NULL;
int exit_flag = 0;

void ebreak(int is_ebreak) {
    if (is_ebreak) {
        exit_flag = 1;
    }
}

static void single_cycle() {
    top->clk = 0;
    top->eval();
    top->clk = 1;
    top->eval();
}

static void reset(int n) {
    top->rst = 1;
    while (n-- > 0) single_cycle();
    top->rst = 0;
}

static void set_inst() {
    paddr_t addr = 0x80000000;
    int len = 4;
    word_t data[] = {
        0b00000000000100000000000010010011, 0b00000000001000001000000000010011,
        0b00000000001100000000000010010011, 0b00000000010000001000000000010011,
        0b00000000010100000000000010010011, 0b00000000011000001000000000010011,
        0b00000000011100000000000010010011, 0b00000000100000001000000000010011,
        0b00000000100100000000000010010011, 0b00000000101000001000000000010011,
    };
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        paddr_write(addr + len * i, len, data[i]);
    }
}

int main(int argc, char **argv, char **env) {
    contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    contextp->traceEverOn(true);
    tfp = new VerilatedFstC;
    top = new Vtop{contextp};
    top->trace(tfp, 0);
    tfp->open("build/waveform.fst");

    set_inst();
    reset(10);
    while (1) {
        top->clk = 0;
        top->eval();
        contextp->timeInc(1);
        tfp->dump(contextp->time());

        top->clk = 1;
        top->inst_in = paddr_read(top->pc_out, 4);
        printf("%x: %x\n", top->pc_out, top->inst_in);
        top->eval();
        contextp->timeInc(1);
        tfp->dump(contextp->time());
    }
    tfp->close();
    delete contextp;
    return 0;
}