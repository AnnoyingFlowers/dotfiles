#include <cstdint>

#include "Vtop.h"
#include "paddr.h"
#include "verilated.h"
#include "verilated_fst_c.h"

Vtop *top = NULL;

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
    word_t data = 0b00000001111100001000000100010011;
    paddr_write(addr, len, data);
}

int main(int argc, char **argv, char **env) {
    VerilatedContext *contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    contextp->traceEverOn(true);             //打开追踪功能
    VerilatedFstC *tfp = new VerilatedFstC;  //初始化FST对象指针
    top = new Vtop{contextp};
    top->trace(tfp, 0);
    tfp->open("build/waveform.fst");

    reset(10);
    int time = 8;
    while (time--) {
        top->clk = 0;
        top->inst_in = paddr_read(top->pc_out, 4);
        printf("%x\n", top->pc_out);
        top->eval();
        contextp->timeInc(1);
        tfp->dump(contextp->time());

        top->clk = 1;
        top->eval();
        contextp->timeInc(1);
        tfp->dump(contextp->time());
    }
    tfp->close();
    delete contextp;
    return 0;
}