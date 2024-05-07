module top(
        input clk,
        input rst,
        input [31:0] inst,
        output [31:0] pc
    );
    wire [4:0] waddr;
    wire [31:0] wdata;
    wire wen;
    wire [4:0] raddr1;
    wire [31:0] rdata1;
    wire [4:0] raddr2;
    wire [31:0] rdata2;
    RegisterFile #(5, 32) R (
                     clk,
                     waddr,
                     wdata,
                     wen,
                     raddr1,
                     rdata1,
                     raddr2,
                     rdata2
                 );

    wire [31:0] rpc_in;
    wire [31:0] rpc_out;
    Reg #(32, 32'h80000000) rpc (clk, rst, rpc_in, rpc_out, 1'b1);

    wire [31:0] rim_in;
    wire [31:0] rim_out;
    Reg #(32, 32'b0) rim (clk, rst, rim_in, rim_out, 1'b1);
    assign rim_in = inst;

    wire [6:0] opcode;
    wire [6:0] funct7;
    wire [2:0] funct3;
    wire [31:0] imm;
    wire [4:0] rs1;
    wire [4:0] rs2;
    wire [4:0] rd;
    Decode decode (inst, opcode, funct7, funct3, imm, rs1, rs2, rd);


    wire [31:0] A;
    wire [31:0] B;
    wire [31:0] S;
    ALU alu (A, B, funct3, S);




endmodule
