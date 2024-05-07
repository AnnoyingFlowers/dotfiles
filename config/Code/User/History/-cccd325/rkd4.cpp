#include <cstdint>

#include "Vtop.h"
#include "paddr.h"
#include "verilated.h"
#include "verilated_fst_c.h"

Vtop *top = NULL;

int main(int argc, char **argv, char **env) {
    VerilatedContext *contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    contextp->traceEverOn(true);             //打开追踪功能
    VerilatedFstC *tfp = new VerilatedFstC;  //初始化FST对象指针
    top = new Vtop{contextp};
    top->trace(tfp, 0);
    tfp->open("build/waveform.fst");
    int time = 8;
    // printf("%u\n", pmem_read(0x80000000, 4));
    while (time--) {
        top->inst = pmem_read(top->pc, 4);
        top->eval();
        contextp->timeInc(1);
        tfp->dump(contextp->time());
    }
    tfp->close();
    delete contextp;
    return 0;
}