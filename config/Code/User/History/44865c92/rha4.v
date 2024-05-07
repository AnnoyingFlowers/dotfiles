module Adder #(DATA_WIDTH = 1) (
        input clk,
        input rst,
        input [DATA_WIDTH-1:0] A,
        input [DATA_WIDTH-1:0] B,
        output [DATA_WIDTH-1:0] S
    );
    assign S = A + B;
endmodule
