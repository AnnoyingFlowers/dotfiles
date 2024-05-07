module Decode (
        input [31:0] inst,
        output [11:0] imm_I,
        output [11:0] imm_S,
        output [12:0] imm_B,
        output [31:0] imm_U,
        output [20:0] imm_J,
        output [4:0] rs1,
        output [4:0] rs2,
        output [4:0] rd
    );
    reg [31:0] imm;
    MuxKeyWithDefault #(2**32, 32, 32) i0 (imm)


                  endmodule
