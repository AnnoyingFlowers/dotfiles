module kbd_ctrl(
        input clk,
        input rst,
        input ps2_clk,
        input ps2_data,
        output is_press,
        output [7:0] count,
        output [7:0] key
    );

    reg nextdata_n = 1'b1;
    reg [23:0] buffer;
    reg [7:0] count_reg;
    wire [7:0] data;
    wire ready;
    wire overflow;

    ps2_keyboard u_ps2_keyboard(
                     .clk(clk),
                     .clrn(rst),
                     .ps2_clk(ps2_clk),
                     .ps2_data(ps2_data),
                     .nextdata_n(nextdata_n),
                     .data(data),
                     .ready(ready),
                     .overflow(overflow)
                 );

    always @(posedge clk) begin
        if(rst == 0) begin
            count_reg <= 8'b0;
            buffer <= 24'b0;
            nextdata_n <= 1'b1;
        end
        else begin
            if(nextdata_n == 1'b0)
                nextdata_n <= 1'b1;
            if(ready || overflow) begin
                if(data != 8'b0) begin
                    nextdata_n <= 1'b0;
                    buffer <= {buffer[15:0], data};
                end
            end
        end
    end

    assign is_press = (buffer[7:0] != 8'b0 && buffer[15:8] != 8'hF0);

    always @(negedge is_press) begin
        count <= count + 8'b1;
        $display("count %x", count_reg);
    end

    assign count = count_reg;

    assign key = buffer[7:0];

endmodule
