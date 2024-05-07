module top(
        input clk,
        input rst,
        input [31:0] inst
    );
    wire [4:0] waddr;
    wire [31:0] wdata;
    wire wen;
    RegisterFile #(5, 32) R (
                     .clk(clk),
                     .waddr(waddr),
                     .wdata(wdata),
                     .wen(wen)
                 );


endmodule
