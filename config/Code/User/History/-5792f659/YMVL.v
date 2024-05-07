module RegisterFile #(ADDR_WIDTH = 1, DATA_WIDTH = 1) (
        input clk,
        input [ADDR_WIDTH-1:0] waddr,
        input [DATA_WIDTH-1:0] wdata,
        input wen,
        input [ADDR_WIDTH-1:0] raddr1,
        output [DATA_WIDTH-1:0] rdata1,
        input [ADDR_WIDTH-1:0] raddr2,
        output [DATA_WIDTH-1:0] rdata2
    );

    reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];

    always @(posedge clk) begin
        if (wen) begin
            if(waddr == {ADDR_WIDTH{1'b0}})
                rf[waddr] <= {DATA_WIDTH{1'b0}};
            else
                rf[waddr] <= wdata;
        end
    end

    assign rdata1 = rf[raddr1];
    assign rdata2 = rf[raddr2];

endmodule