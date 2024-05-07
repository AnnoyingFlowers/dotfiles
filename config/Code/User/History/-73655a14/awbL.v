module barrel_shifter8(
        input [7:0] din,
        input [2:0] shamt,
        input LR,
        input AL,
        output [7:0] dout
    );

    mux21a m21(
               .a({din[7], 0}),
               .s(AL),
           );

endmodule
