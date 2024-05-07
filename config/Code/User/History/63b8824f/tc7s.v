module bcd7seg(
        input  [3:0] b,
        output  [6:0] h
    );

    wire [6:0] segs [9:0];
    assign segs[0] = 7'b1111110;
    assign segs[1] = 7'b0110000;
    assign segs[2] = 7'b1101101;
    assign segs[3] = 7'b1111001;
    assign segs[4] = 7'b0110011;
    assign segs[5] = 7'b1011011;
    assign segs[6] = 7'b1011111;
    assign segs[7] = 7'b1110000;
    assign segs[8] = 7'b1111111;
    assign segs[9] = 7'b1111011;

    assign h = (h == 7'b0000000) ? 7'b1111111 : segs[b];

endmodule
