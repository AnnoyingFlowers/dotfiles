`timescale 1ns / 1ps
module top(
        input clk,
        input rst,
        input ps2_clk,
        input ps2_data,
        output [7:0] key,
        output [7:0] ascii,
        output [7:0] count,
        output is_press
    );

    kbd_ctrl u_kbd_ctrl(
                 .clk        	( clk         ),
                 .rst       	( rst         ),
                 .ps2_clk    	( ps2_clk     ),
                 .ps2_data   	( ps2_data    ),
                 .is_press 	    ( is_press    ),
                 .count         ( count       ),
                 .key           ( key         )
             );

    key2ascii u_key2ascii(
                  .data   	( key    ),
                  .ascii 	( ascii   )
              );

    wire [3:0] b;
    wire [7:0] h;

    hex7seg key_hex7seg(
                .b 	( b  ),
                .h 	( h  )
            );

    hex7seg ascii_hex7seg(
                .b 	( b  ),
                .h 	( h  )
            );


endmodule
