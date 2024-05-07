module alu(
        input [2:0] op,
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

    wire [3:0] Result;
    wire Carry;
    wire Zero;
    wire Overflow;

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
        case(op)
            3'b000: begin
                Cin = 0;
                A = in_x;
                B = in_y;
                out_s = Result;
                out_c = Carry;
                zero = Zero;
                overflow = Overflow;
            end
            3'b001: begin
                Cin = 1;
                A = in_x;
                B = {4{Cin}} ^ in_y;
                out_s = Result;
                out_c = Carry;
                zero = Zero;
                overflow = Overflow;
            end
            3'b010: begin
                Cin = 0;
                A = ~in_x;
                B = 0;
                out_s = Result;
                out_c = 0;
                zero = Zero;
                overflow = 0;
            end
            3'b011: begin
                Cin = 0;
                A = in_x & in_y;
                B = 0;
                out_s = Result;
                out_c = 0;
                zero = Zero;
                overflow = 0;
            end
            3'b100: begin
                Cin = 0;
                A = in_x | in_y;
                B = 0;
                out_s = Result;
                out_c = 0;
                zero = Zero;
                overflow = 0;
            end
            3'b101: begin
                Cin = 0;
                A = in_x ^ in_y;
                B = 0;
                out_s = Result;
                out_c = 0;
                zero = Zero;
                overflow = 0;
            end
            3'b110: begin
                Cin = 1;
                A = in_x;
                B = {4{Cin}} ^ in_y;
                out_s = {{3{1'b0}}, Result[3] ^ Overflow};
                out_c = 0;
                zero = Zero;
                overflow = 0;
            end
            3'b111: begin
                Cin = 1;
                A = in_x;
                B = {4{Cin}} ^ in_y;
                out_s = {{3{1'b0}}, Zero};
                out_c = 0;
                zero = Zero;
                overflow = 0;
            end
            default: begin
                Cin = 0;
                A = 0;
                B = 0;
                out_s = Result;
                out_c = Carry;
                zero = Zero;
                overflow = Overflow;
            end
        endcase


    end

endmodule
