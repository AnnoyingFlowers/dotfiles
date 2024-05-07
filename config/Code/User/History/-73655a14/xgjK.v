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
    wire m41_0_0_w;
    mux41ab m41_0_0(
                .a({1'b0, din[0], din[1], din[0]}),
                .s({LR, shamt[0]}),
                .y(m41_0_0_w)
            );
    wire m41_0_1_w;
    mux41ab m41_0_1(
                .a({din[0], din[1], din[2], din[1]}),
                .s({LR, shamt[0]}),
                .y(m41_0_1_w)
            );
    wire m41_0_2_w;
    mux41ab m41_0_2(
                .a(),
                .s(),
                .y(m41_0_2_w)
            );
    wire m41_0_3_w;
    mux41ab m41_0_3(
                .a(),
                .s(),
                .y(m41_0_3_w)
            );
    wire m41_0_4_w;
    mux41ab m41_0_4(
                .a(),
                .s(),
                .y(m41_0_4_w)
            );
    wire m41_0_5_w;
    mux41ab m41_0_5(
                .a(),
                .s(),
                .y(m41_0_5_w)
            );
    wire m41_0_6_w;
    mux41ab m41_0_6(
                .a(),
                .s(),
                .y(m41_0_6_w)
            );
    wire m41_0_7_w;
    mux41ab m41_0_7(
                .a(),
                .s(),
                .y(m41_0_7_w)
            );
    wire m41_1_0_w;
    mux41ab m41_1_0(
                .a(),
                .s(),
                .y(m41_1_0_w)
            );
    wire m41_1_1_w;
    mux41ab m41_1_1(
                .a(),
                .s(),
                .y(m41_1_1_w)
            );
    wire m41_1_2_w;
    mux41ab m41_1_2(
                .a(),
                .s(),
                .y(m41_1_2_w)
            );
    wire m41_1_3_w;
    mux41ab m41_1_3(
                .a(),
                .s(),
                .y(m41_1_3_w)
            );
    wire m41_1_4_w;
    mux41ab m41_1_4(
                .a(),
                .s(),
                .y(m41_1_4_w)
            );
    wire m41_1_5_w;
    mux41ab m41_1_5(
                .a(),
                .s(),
                .y(m41_1_5_w)
            );
    wire m41_1_6_w;
    mux41ab m41_1_6(
                .a(),
                .s(),
                .y(m41_1_6_w)
            );
    wire m41_1_7_w;
    mux41ab m41_1_7(
                .a(),
                .s(),
                .y(m41_1_7_w)
            );
    wire m41_2_0_w;
    mux41ab m41_2_0(
                .a(),
                .s(),
                .y(m41_2_0_w)
            );
    wire m41_2_1_w;
    mux41ab m41_2_1(
                .a(),
                .s(),
                .y(m41_2_1_w)
            );
    wire m41_2_2_w;
    mux41ab m41_2_2(
                .a(),
                .s(),
                .y(m41_2_2_w)
            );
    wire m41_2_3_w;
    mux41ab m41_2_3(
                .a(),
                .s(),
                .y(m41_2_3_w)
            );
    wire m41_2_4_w;
    mux41ab m41_2_4(
                .a(),
                .s(),
                .y(m41_2_4_w)
            );
    wire m41_2_5_w;
    mux41ab m41_2_5(
                .a(),
                .s(),
                .y(m41_2_5_w)
            );
    wire m41_2_6_w;
    mux41ab m41_2_6(
                .a(),
                .s(),
                .y(m41_2_6_w)
            );
    wire m41_2_7_w;
    mux41ab m41_2_7(
                .a(),
                .s(),
                .y(m41_2_7_w)
            );

endmodule
