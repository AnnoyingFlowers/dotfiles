module shift_rigister #(parameter N = 8) (
        input clk,
        input rst,
        input [2:0] ctrl,
        input in,
        output [N-1:0] out
    );

    always @(posedge clk) begin
        case(ctrl)
            3'd0:
                out =
            endcase
    end

endmodule
