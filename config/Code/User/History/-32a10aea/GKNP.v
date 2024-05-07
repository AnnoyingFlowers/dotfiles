module Decode (
        input [31:0] inst,
        output reg [31:0] imm,
        output reg [4:0] rs1,
        output reg [4:0] rs2,
        output reg [4:0] rd
    );
    MuxKeyWithDefault #(2**32, 32, 47) i0 ({imm, rs1, rs2, rd}, inst, 47'b0, {
                                               32'b??
                                           });


endmodule
