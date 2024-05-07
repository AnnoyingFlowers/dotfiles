#include "obj_dir/Vpri_encode42.h"
#include "verilated.h"
#include "verilated_fst_c.h"

VerilatedContext* contextp = NULL;
VerilatedFstC* tfp = NULL;

static Vpri_encode42* top;

void step_and_dump_wave() {
    top->eval();
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}
void sim_init() {
    contextp = new VerilatedContext;
    tfp = new VerilatedFstC;
    top = new Vpri_encode42;
    contextp->traceEverOn(true);
    top->trace(tfp, 0);
    tfp->open("dump.fst");
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
                 top->x =0b0011; step_and_dump_wave();
                 top->x =0b0111; step_and_dump_wave();
                 top->x =0b1111; step_and_dump_wave();
                 top->x =0b1100; step_and_dump_wave();
                 top->x =0b0110; step_and_dump_wave();
                 top->x =0b1110; step_and_dump_wave();

    top->en=0b1; top->x =0b0000; step_and_dump_wave();
                 top->x =0b0001; step_and_dump_wave();
                 top->x =0b0010; step_and_dump_wave();
                 top->x =0b0100; step_and_dump_wave();
                 top->x =0b1000; step_and_dump_wave();
                 top->x =0b0011; step_and_dump_wave();
                 top->x =0b0111; step_and_dump_wave();
                 top->x =0b1111; step_and_dump_wave();
                 top->x =0b1100; step_and_dump_wave();
                 top->x =0b0110; step_and_dump_wave();
                 top->x =0b1110; step_and_dump_wave();
    // clang-format on
    sim_exit();
}