module top(
        input [2:0] op,
        input [3:0] in_x,
        input [3:0] in_y,
        output reg [3:0] out_s,
        output reg out_c,
        output reg zero,
        output reg overflow
    );

    alu u_alu(
            .op(op),
            .in_x(in_x),
            .in_y(in_y),
            .out_s(out_s),
            .out_c(out_c),
            .zero(zero),
            .overflow(overflow)
        );

endmodule
