#include "obj_dir/Vmux41_dual.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

VerilatedContext* contextp = NULL;
VerilatedVcdC* tfp = NULL;

static Vmux41_dual* top;

void step_and_dump_wave() {
    top->eval();
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}
void sim_init() {
    contextp = new VerilatedContext;
    tfp = new VerilatedVcdC;
    top = new Vmux41_dual;
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
    top->y=0b00;  top->X0=0b11; top->X1=0b01; top->X2=0b00;  top->X3=0b10; step_and_dump_wave();
                  top->X0=0b10; top->X1=0b01; top->X2=0b01;  top->X3=0b00; step_and_dump_wave();
    top->Y=0b01;  top->X0=0b11; top->X1=0b01; top->X2=0b00;  top->X3=0b10; step_and_dump_wave();
                  top->X0=0b10; top->X1=0b01; top->X2=0b01;  top->X3=0b00; step_and_dump_wave();
    top->Y=0b10;  top->X0=0b11; top->X1=0b01; top->X2=0b00;  top->X3=0b10; step_and_dump_wave();
                  top->X0=0b10; top->X1=0b01; top->X2=0b01;  top->X3=0b00; step_and_dump_wave();
    top->y=0b11;  top->X0=0b11; top->X1=0b01; top->X2=0b00;  top->X3=0b10; step_and_dump_wave();
                  top->X0=0b10; top->X1=0b01; top->X2=0b01;  top->X3=0b00; step_and_dump_wave();

    sim_exit();
}