module shift_register #(parameter N = 8) (
        input clk,
        input rst,
        input [2:0] ctrl,
        input [N-1:0] in,
        output reg [N-1:0] out
    );

    reg [N-1:0] dff;

    always @(posedge clk) begin
        if(rst)
            dff <= {N{1'b0}};
        else begin
            case(ctrl)
                3'd0:
                    dff <= {N{1'b0}};
                3'd1:
                    dff <= in;
                3'd2:
                    dff <= {1'b0, dff[N-1:1]};
                3'd3:
                    dff <= {dff[N-2:0], 1'b0};
                3'd4:
                    dff <= {dff[N-1], dff[N-1:1]};
                3'd5:
                    dff <= {in[0], dff[N-1:1]};
                3'd6:
                    dff <= {dff[0], dff[N-1:1]};
                3'd7:
                    dff <= {dff[N-2:0], dff[N-1]};
            endcase
        end
    end

endmodule
