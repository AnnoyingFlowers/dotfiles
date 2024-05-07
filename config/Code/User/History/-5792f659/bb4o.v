module RegisterFile #(ADDR_WIDTH = 1, DATA_WIDTH = 1) (
        input clk,
        input [DATA_WIDTH-1:0] wdata,
        input [ADDR_WIDTH-1:0] waddr,
        input wen,
        input [ADDR_WIDTH-1:0] raddr,
        output [DATA_WIDTH-1:0] rdata,
        input ren
    );

    reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];
    always @(posedge clk) begin
        if (wen)
            rf[waddr] <= wdata;
    end

    assign rdata = rf[waddr];

endmodule