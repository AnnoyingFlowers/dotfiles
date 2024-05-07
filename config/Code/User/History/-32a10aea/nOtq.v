module Decode (
        input [31:0] inst,
        output [6:0] opcode,
        output [6:0] funct7,
        output [2:0] funct3,
        output reg [31:0] imm,
        output reg [4:0] rs1,
        output reg [4:0] rs2,
        output reg [4:0] rd
    );
    MuxKeyWithDefault #(1, 7, 7+7+3+32+5+5+5) i0 ({imm, rs1, rs2, rd}, inst, 1'b0, {
                          32'b??
                      });


endmodule
