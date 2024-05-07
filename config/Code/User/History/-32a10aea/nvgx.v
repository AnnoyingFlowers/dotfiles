import "DPI-C" function void ebreak(input int is_ebreak);

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
               wire is_ebreak = inst == 32'b00000000000100000000000001110011;
               always @(*) begin
                   if(is_ebreak == 1'b1)
                       ebreak();
               end
               MuxKeyWithDefault #(1, 7, 64) i0 ({opcode, funct7, funct3, imm, rs1, rs2, rd}, inst[6:0], 64'b0, {
                                                     7'b0010011, {inst[6:0], 7'b0, inst[14:12], {{20{inst[31]}}, inst[31:20]}, inst[19:15], 5'b0, inst[11:7]}
                                                 });

           endmodule
