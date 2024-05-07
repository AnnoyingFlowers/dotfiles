module alu(
        input [3:0] a,
        input [3:0] b,
        output reg [3:0] result,
        output reg carry,
        output reg zero,
        output reg overflow
    );
    assign result = a + b;
endmodule
