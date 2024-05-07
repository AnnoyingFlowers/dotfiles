module top(
        input [2:0] select,
        input in_c,
        input [3:0] in_x,
        input [3:0] in_y,
        output reg [3:0] out_s,
        output reg out_c,
        output reg zero,
        output reg overflow
    );

    reg Cin;
    reg [3:0] A;
    reg [3:0] B;

    reg [3:0] Result;
    reg Carry;
    reg Zero;
    reg Overflow;

    adder u_adder(
              .Cin(Cin),
              .A(A),
              .B(B),
              .Result(Result),
              .Carry(Carry),
              .Zero(Zero),
              .Overflow(Overflow)
          );

    always @(*) begin
        case(select)
            3'b000: begin
                Cin = 0;
                A = in_x;
                B = in_y;
                out_s = Result;
                out_c = Carry;
                overflow = Overflow;
                zero = Zero;
            end
            3'b001: begin
                Cin = 1;
                A = in_x;
                B = {4{in_c}} ^ in_y;
                out_s = Result;
                out_c = Carry;
                overflow = Overflow;
                zero = Zero;
            end
            3'b010: begin
                Cin = 0;
                A = ~in_x;
                B = 0;
                out_s = Result;
                out_c = Carry;
                overflow = Overflow;
            end
            3'b011: begin
                Cin = 0;
                A = in_x & in_y;
                B = 0;
                out_s = Result;
                out_c = Carry;
                overflow = Overflow;
            end

        endcase
    end

endmodule
