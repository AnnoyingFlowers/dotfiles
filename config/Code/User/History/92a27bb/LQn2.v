module adder(
        input Cin,
        input [3:0] A,
        input [3:0] B,
        output reg [3:0] Result,
        output reg Carry,
        output reg Zero,
        output reg Overflow
    );
    assign {out_c, out_s} = in_x + in_y + {4'b0000, Cin};
    assign Overflow = (in_x[3] == in_y[3] && out_s[3] != in_x[3]);
    assign zero = ~(| out_s);

endmodule
