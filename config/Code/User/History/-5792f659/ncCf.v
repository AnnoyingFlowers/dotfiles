module RegisterFile #(ADDR_WIDTH = 1, DATA_WIDTH = 1) (
        input clk,
        input [DATA_WIDTH-1:0] wdata,
        input [ADDR_WIDTH-1:0] waddr,
        input wen,
        output [DATA_WIDTH-1:0] rdata
    );

    wire [ADDR_WIDTH-1:0] read_addr;
    wire [DATA_WIDTH-1:0] read_data;

    reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];
    always @(posedge clk) begin
        if (wen)
            rf[waddr] <= wdata;
    end

    assign read_addr = wen ? waddr : {ADDR_WIDTH{1'bx}};
    MuxKeyWithDefault #(2**ADDR_WIDTH, ADDR_WIDTH, DATA_WIDTH) i0 (rdata, waddr, {ADDR_WIDTH{1'b0}}, {

                      });


endmodule
