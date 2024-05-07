module ALU (
        input [31:0] A,
        input [31:0] B,
        input [2:0] funct3,
        output [31:0] S
    );

    MuxKeyWithDefault #(1, 3, 32) i0 (S, funct3, 32'b0, {
                                          3'b000, A + B
                                      });

endmodule
