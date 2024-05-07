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
    // reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];

    wire [DATA_WIDTH-1:0] in;
    wire [DATA_WIDTH-1:0] out;
    Reg #(DATA_WIDTH, {DATA_WIDTH{1'b0}}) rf (clk, rst, in, out, wen) [2**ADDR_WIDTH-1:0];
    genvar i;
    generate
        for (i = 0; i < NUM_MODULES; i = i + 1) begin : gen_regfile
            RegisterFile #(
                             .ADDR_WIDTH(ADDR_WIDTH),
                             .DATA_WIDTH(DATA_WIDTH)
                         ) rf_instance (
                             .clk(clk),
                             .waddr(waddr[i]),
                             .wdata(wdata[i]),
                             .wen(wen[i]),
                             .raddr(raddr[i]),
                             .rdata(rdata[i])
                         );
        end
    endgenerate

    always @(posedge clk) begin
        if (wen)
            rf[waddr] <= wdata;
    end

    assign rdata1 = raddr1 == {ADDR_WIDTH{1'b0}} ? {DATA_WIDTH{1'b0}} : rf[raddr1];
    assign rdata2 = raddr2 == {ADDR_WIDTH{1'b0}} ? {DATA_WIDTH{1'b0}} : rf[raddr2];

endmodule
