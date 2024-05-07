// DESCRIPTION: Verilator: Verilog example module
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2017 by Wilson Snyder.
// SPDX-License-Identifier: CC0-1.0
//======================================================================

// Include common routines
#include <verilated.h>

// Include model header, generated from Verilating "top.v"
#include "Vkeyboard_sim.h"
#include "verilated_fst_c.h"

int main(int argc, char** argv) {
    // See a similar example walkthrough in the verilator manpage.

    // This is intended to be a minimal example.  Before copying this to start a
    // real project, it is better to start with a more complete example,
    // e.g. examples/c_tracing.

    // Construct a VerilatedContext to hold simulation time, etc.
    VerilatedContext* contextp = new VerilatedContext;

    // Pass arguments so Verilated code can see them, e.g. $value$plusargs
    // This needs to be called before you create any model
    contextp->commandArgs(argc, argv);
    contextp->traceEverOn(true);             //打开追踪功能
    VerilatedFstC* tfp = new VerilatedFstC;  //初始化FST对象指针

    // Construct the Verilated model, from Vtop.h generated from Verilating
    // "top.v"
    Vkeyboard_sim* top = new Vkeyboard_sim{contextp};
    top->trace(tfp, 0);

    // Simulate until $finish
    while (!contextp->gotFinish()) {
        // Evaluate model
        top->eval();
        tfp->dump(contextp->time());
        contextp->timeInc(1);
    }

    // Final model cleanup
    top->final();
    tfp->close();

    // Destroy model
    delete top;

    // Return good completion status
    return 0;
}