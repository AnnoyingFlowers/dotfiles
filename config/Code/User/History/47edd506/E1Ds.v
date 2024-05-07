module shift_rigister #(parameter N = 8) (
        input clk,
        input rst,
        input [2:0] ctrl,
        input [N-1:0] in,
        output reg [N-1:0] out
    );

    reg [N-1:0] rigister;

    always @(posedge clk) begin
        if(rst)
            rigister <= {N{1'b0}};
        else begin
            case(ctrl)
                3'd0:
                    rigister <= {N{1'b0}};
                3'd1:
                    rigister <= in;
                3'd2:
                    rigister <= {1'b0, rigister[N-1:1]};
                3'd3:
                    rigister <= {rigister[N-2:0], 1'b0};
            endcase
        end
    end

endmodule
