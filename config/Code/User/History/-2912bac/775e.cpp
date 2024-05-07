#include <nvboard.h>

#include <cstdint>

#include "Vmux41_dual.h"
#include "verilated.h"
#include "verilated_fst_c.h"

TOP_NAME *dut = NULL;

void nvboard_bind_all_pins(TOP_NAME *top);

static void single_cycle() {
    dut->eval();
}

int main(int argc, char **argv, char **env) {
    VerilatedContext *contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    contextp->traceEverOn(true);             //打开追踪功能
    VerilatedFstC *tfp = new VerilatedFstC;  //初始化FST对象指针
    dut = new Vtop{contextp};
    dut->trace(tfp, 0);
    nvboard_bind_all_pins(dut);
    nvboard_init();
    // tfp->open("build/waveform.fst");

    while (!contextp->gotFinish()) {
        nvboard_update();
        single_cycle();
        if ((contextp->time() & 0b1111) == 0) {
            tfp->dump(contextp->time() >> 4);
        }
        contextp->timeInc(1);
    }
    nvboard_quit();
    tfp->close();
    delete contextp;
    return 0;
}