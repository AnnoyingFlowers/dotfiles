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
    wire Cin;
    wire [3:0] A;
    wire [3:0] B;
    wire  [3:0] Result;
    wire  Carry;
    wire  Zero;
    wire  Overflow;

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
            1'd0: begin
                Cin = 0;
                A = in_x;
                B = in_y;
            end
            1'd1: begin
                Cin = 1;
                A = in_x;
                B = {4{in_c}} ^ in_y;

            end

        endcase
    end

endmodule
