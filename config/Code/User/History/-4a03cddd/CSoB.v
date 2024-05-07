module top (
        input  [7:0] x,
        input  en,
        output reg [6:0] h,
        output idc,
        output reg [2:0] y
    );

    pri_encode83 u_pri_encode83(
                     .x   (x  ),
                     .en  (en ),
                     .idc (idc),
                     .y   (y  )
                 );
    bcd7seg u_bcd7seg(
                .b({idc, y}),
                .h(h)
            );


endmodule //top
