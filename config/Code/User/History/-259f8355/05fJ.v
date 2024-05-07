module pri_encode83(x,en,idc,y);
    input  [7:0] x;
    input  en;
    output reg idc;
    output reg [2:0]y;
    integer i;

    always @(x or en) begin
        if (en) begin
            y = 0;
            idc <= 0;
            for( i = 0; i <= 7; i = i+1) begin
                if(x[i] == 1) begin
                    y = i[2:0];
                    idc <= 1;
                end
            end
        end
        else
            y = 0;
    end
endmodule
