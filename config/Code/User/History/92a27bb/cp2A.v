module alu(
        input [3:0] in_x,
        input [3:0] in_y,
        output reg [3:0] out_s,
        output reg out_c,
        output reg zero,
        output reg overflow
    );
    assign {out_c, out_s} = in_x + in_y;
    assign overflow = (in_x[3] == in_y[3] && out_s[3] != in_x[3]);

endmodule
