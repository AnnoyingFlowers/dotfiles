module top(
        input clk,
        input rst,
        input ps2_clk,
        input ps2_data,
        output [7:0] key_lo_seg,
        output [7:0] key_hi_seg,
        output [7:0] seg2,
        output [7:0] ascii_lo_seg,
        output [7:0] ascii_hi_seg,
        output [7:0] seg5,
        output [7:0] count_lo_seg,
        output [7:0] count_hi_seg,
        output is_press
    );

    wire [7:0] count;
    wire [7:0] key;

    kbd_ctrl u_kbd_ctrl(
                 .clk        	( clk         ),
                 .rst       	( rst         ),
                 .ps2_clk    	( ps2_clk     ),
                 .ps2_data   	( ps2_data    ),
                 .is_press 	    ( is_press    ),
                 .count         ( count       ),
                 .key           ( key         )
             );

    wire [7:0] ascii;

    key2ascii u_key2ascii(
                  .data   	( key    ),
                  .ascii 	( ascii   )
              );

    hex7seg key_lo_hex7seg(
                .b 	( key[3:0]  ),
                .h 	( key_lo_seg  )
            );
    hex7seg key_hi_hex7seg(
                .b 	( key[7:4]  ),
                .h 	( key_hi_seg  )
            );

    assign seg2 = 8'b11111111;

    hex7seg ascii_lo_hex7seg(
                .b 	( ascii[3:0]  ),
                .h 	( ascii_lo_seg  )
            );
    hex7seg ascii_hi_hex7seg(
                .b 	( ascii[7:4]  ),
                .h 	( ascii_hi_seg  )
            );

    assign seg5 = 8'b11111111;

    hex7seg count_lo_hex7seg(
                .b 	( count[3:0]  ),
                .h 	( count_lo_seg  )
            );
    hex7seg count_hi_hex7seg(
                .b 	( count[7:4]  ),
                .h 	( count_hi_seg  )
            );


endmodule
