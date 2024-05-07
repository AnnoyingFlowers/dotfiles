`timescale 1ns / 1ps
module top(
        input clk,
        input rst,
        input ps2_clk,
        input ps2_data
    );

    wire is_press;
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

    key2ascii u_key2ascii(
                  .data   	( data    ),
                  .ascii 	( ascii   )
              );


    hex7seg u_hex7seg(
                .b 	( b  ),
                .h 	( h  )
            );


endmodule