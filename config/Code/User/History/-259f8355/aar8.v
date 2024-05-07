module pri_encode83(x,en,idc,y);
    input  [7:0] x;
    input  en;
    output idc;
    output reg [2:0]y;
    integer i;

    assign idc = x == 8'b00000000 ? 1'b0 : 1'b1;

    always @(x or en) begin
        if (en) begin
            y = 0;
            for( i = 0; i <= 7; i = i+1) begin
                if(x[i] == 1) begin
                    y = i[2:0];
                end
            end
        end
        else
            y = 0;
    end
endmodule
