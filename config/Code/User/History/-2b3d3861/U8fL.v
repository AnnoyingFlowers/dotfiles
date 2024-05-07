module top(
        input clk,
        input rst,
        input [2:0] ctrl,
        input [8:0] in,
        output reg [8:0] out
    );

    // outports wire
    wire [N-1:0] 	out;

    shift_register #(.N(8))u_shift_register
                   (
                       .clk  	( clk   ),
                       .rst  	( rst   ),
                       .ctrl 	( ctrl  ),
                       .in   	( in    ),
                       .out  	( out   )
                   );


endmodule
