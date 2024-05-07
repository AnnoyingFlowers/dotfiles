module adder(
        input Cin,
        input [3:0] A,
        input [3:0] B,
        output reg [3:0] Result,
        output reg Carry,
        output reg Zero,
        output reg Overflow
    );
    assign {Carry, Result} = A + B + {4'b0000, Cin};
    assign Overflow = (A[3] == B[3] && Result[3] != A[3]);
    assign Zero = ~(| Result);

endmodule
