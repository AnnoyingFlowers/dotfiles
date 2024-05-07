module alu(
        input [3:0] a,
        input [3:0] b,
        output reg [3:0] result,
        output reg carry,
        output reg zero,
        output reg overflow
    );
    assign {carry, result} = a + b;
    assign overflow = (a[3] == b[3] && result[3] != a[3]);
endmodule
