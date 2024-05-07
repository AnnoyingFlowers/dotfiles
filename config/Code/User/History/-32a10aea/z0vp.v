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
    MuxKeyWithDefault #(1, 7, 64) i0 ({opcode, funct7, funct3, imm, rs1, rs2, rd}, inst[6:0], 64'b0, {
                                          32'b??
                                      });


endmodule
