module LFSR #(parameter N = 8) (
        input clk,
        input rst,
        input [N-1:0] in,
        output reg [N-1:0] out
    );

    reg [N:0] dff;

    always @(posedge clk) begin
        if(rst)
            dff <= {{N+1{1'b0}}[N:1], 1'b1};
        else begin
            dff[N] <= dff[4] ^ dff[3] ^ dff[2] ^ dff[0];
        end
    end

    assign out = dff[N:1];

endmodule
