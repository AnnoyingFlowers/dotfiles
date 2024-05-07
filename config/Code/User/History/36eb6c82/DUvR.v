module hex7seg(
        input  [3:0] b,
        output reg [7:0] h
    );

    wire [6:0] segs [9:0];
    assign segs[0] = 8'b1111110;
    assign segs[1] = 8'b0110000;
    assign segs[2] = 8'b1101101;
    assign segs[3] = 8'b1111001;
    assign segs[4] = 8'b0110011;
    assign segs[5] = 8'b1011011;
    assign segs[6] = 8'b1011111;
    assign segs[7] = 8'b1110000;
    assign segs[8] = 8'b1111111;
    assign segs[9] = 8'b1111011;

    assign h = ~segs[b];

endmodule
