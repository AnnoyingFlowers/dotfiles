module top (
        input  [7:0] x,
        input  en,
        output idc,
        output reg [2:0]y
    );

    pri_encode83 u_pri_encode83(
                     .x   	( x    ),
                     .en  	( en   ),
                     .idc 	( idc  ),
                     .y   	( y    )
                 );


endmodule //top
