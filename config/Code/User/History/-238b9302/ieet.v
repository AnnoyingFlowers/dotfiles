`timescale 1ns / 1ps
module top(
        input clk,
        input rst,
        input ps2_clk,
        input ps2_data,
        output [7:0] key_seg,
        output [7:0] ascii_seg,
        output [7:0] count,
        output is_press
    );

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

    hex7seg key_hi_hex7seg(
                .b 	( key[7:4]  ),
                .h 	( h  )
            );
    hex7seg key_lo_hex7seg(
                .b 	( key[3:0]  ),
                .h 	( h  )
            );

    hex7seg ascii_hi_hex7seg(
                .b 	( ascii[7:4]  ),
                .h 	( h  )
            );
    hex7seg ascii_lo_hex7seg(
                .b 	( ascii[3:0]  ),
                .h 	( h  )
            );


endmodule
