module Decode (
        input [31:0] inst,
        output reg [6:0] opcode,
        output reg [6:0] funct7,
        output reg [2:0] funct3,
        output reg [31:0] imm,
        output reg [4:0] rs1,
        output reg [4:0] rs2,
        output reg [4:0] rd
    );
    MuxKeyWithDefault #(1, 32, 64) i0 ({opcode, funct7, funct3, imm, rs1, rs2, rd}, inst, 64'b0, {
                                           32'bzzzzzzzzzzzzzzzzz000zzzzz0010011, {inst[6:0], 7'b0, inst[14:12], {{20{inst[31]}}, inst[31:20]}, inst[19:15], 5'b0, inst[11:7]}

                                       });


endmodule
