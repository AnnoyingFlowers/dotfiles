module top (

    );
    // outports wire
    wire       	idc;
    wire [2:0] 	y;

    pri_encode83 u_pri_encode83(
                     .x   	( x    ),
                     .en  	( en   ),
                     .idc 	( idc  ),
                     .y   	( y    )
                 );


endmodule //top
