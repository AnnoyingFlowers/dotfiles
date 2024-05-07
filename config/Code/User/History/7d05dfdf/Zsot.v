module LFSR #(parameter N = 8) (
        input clk,
        input rst,
        input [N-1:0] in,
        output reg [N-1:0] out
    );

    reg [N:0] dff;

    always @(posedge clk) begin
        if(rst)
            dff <= {N+1{1'b0}};
        else begin
            case(dff)
                {N+1{1'b0}}:
                    dff <= dff | 1'b1;
                default:
                    dff[N] <= dff[4] ^ dff[3] ^ dff[2] ^ dff[0];
            endcase
        end
    end

    assign out = dff[N:1];

endmodule
