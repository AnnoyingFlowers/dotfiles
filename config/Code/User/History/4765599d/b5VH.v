module top(
        input clk,
        input rst,
        input [31:0] inst,
        output [31:0] pc
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
    wire [31:0] rpc_in;
    wire [31:0] rpc_out;
    Reg #(32, 32'h80000000) rpc (clk, rst, rpc_in, rpc_out, 1'b1);


endmodule
