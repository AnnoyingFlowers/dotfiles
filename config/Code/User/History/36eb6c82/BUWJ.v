module hex7seg(
        input  [3:0] b,
        output reg [7:0] h
    );

    wire [7:0] segs [9:0];
    assign segs[0] = 8'b11111100;
    assign segs[1] = 8'b01100000;
    assign segs[2] = 8'b11011010;
    assign segs[3] = 8'b11110010;
    assign segs[4] = 8'b01100110;
    assign segs[5] = 8'b10110110;
    assign segs[6] = 8'b10111110;
    assign segs[7] = 8'b11100000;
    assign segs[8] = 8'b11111110;
    assign segs[9] = 8'b11110110;

    assign h = ~segs[b];

endmodule
