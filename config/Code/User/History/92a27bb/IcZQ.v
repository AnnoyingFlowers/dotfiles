module adder #(parameter N = 4) (
        input Cin,
        input [N-1:0] A,
        input [N-1:0] B,
        output reg [N-1:0] Result,
        output reg Carry,
        output reg Zero,
        output reg Overflow
    );
    reg out_c;
    assign {out_c, Result} = A + B + {{N-1{1'b0}},Cin};
    assign Carry = out_c ^ Cin;
    assign Overflow = (A[N-1] == B[N-1] && Result[N-1] != A[N-1]);
    assign Zero = ~(| Result);

endmodule
