module alu(
        input [3:0] in_x,
        input [3:0] in_y,
        output reg [3:0] out_s,
        output reg carry,
        output reg zero,
        output reg overflow
    );
    assign {carry, out_s} = a + b;
    assign overflow = (a[3] == b[3] && out_s[3] != a[3]);
endmodule
