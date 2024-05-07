module pri_encode83(x,en,idc,y);
    input  [7:0] x;
    input  en;
    output idc;
    output reg [2:0]y;
    integer i;
    always @(x or en) begin
        if (en) begin
            y = 0;
            for( i = 0; i <= 3; i = i+1)
                if(x[i] == 1)
                    y = i[1:0];
        end
        else
            y = 0;
    end
endmodule
