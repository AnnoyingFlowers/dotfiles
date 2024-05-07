#include "obj_dir/Vmux21.h"
#include "verilated.h"
#include "verilated_fst_c.h"

VerilatedContext* contextp = NULL;
VerilatedFstC* tfp = NULL;

static Vmux21* top;

void step_and_dump_wave() {
    top->eval();
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}
void sim_init() {
    contextp = new VerilatedContext;
    tfp = new VerilatedFstC;
    top = new Vmux21;
    contextp->traceEverOn(true);
    top->trace(tfp, 0);
    tfp->open("dump.vcd");
}

void sim_exit() {
    step_and_dump_wave();
    tfp->close();
}

int main() {
    sim_init();
    // clang-format off
  top->en=0b0; top->x =0b0000; step_and_dump_wave();
               top->x =0b0001; step_and_dump_wave();
               top->x =0b0010; step_and_dump_wave();
               top->x =0b0100; step_and_dump_wave();
               top->x =0b1000; step_and_dump_wave();
  top->en=0b1; top->x =0b0000; step_and_dump_wave();
               top->x =0b0001; step_and_dump_wave();
               top->x =0b0010; step_and_dump_wave();
               top->x =0b0100; step_and_dump_wave();
               top->x =0b1000; step_and_dump_wave();
  sim_exit();
}