module adder(
        input Cin,
        input [3:0] A,
        input [3:0] B,
        output reg [3:0] Result,
        output reg Carry,
        output reg Zero,
        output reg Overflow
    );
    reg out_c;
    assign {out_c, Result} = A + B + {{3{1'b0}},Cin};
    assign Carry = Carry ^ Cin;
    assign Overflow = (A[3] == B[3] && Result[3] != A[3]);
    assign Zero = ~(| Result);

endmodule
