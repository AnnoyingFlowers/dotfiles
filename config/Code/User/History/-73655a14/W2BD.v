module barrel_shifter8(
        input [7:0] din,
        input [2:0] shamt,
        input LR,
        input AL,
        output [7:0] dout
    );

    wire m21_w;
    mux21a m21(
               .a({din[7], 1'b0}),
               .s(AL),
               .y(m21_w)
           );

endmodule
