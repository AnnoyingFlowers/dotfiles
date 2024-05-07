
// shift_register
// module top(
//         input clk,
//         input rst,
//         input [2:0] ctrl,
//         input [7:0] in,
//         output reg [7:0] out
//     );
//
//     shift_register #(.N(8)) u_shift_register (
//                        .clk  	( clk   ),
//                        .rst  	( rst   ),
//                        .ctrl 	( ctrl  ),
//                        .in   	( in    ),
//                        .out  	( out   )
//                    );
//
//
// endmodule

module top(
        input [7:0] din,
        input [2:0] shamt,
        input LR,
        input AL,
        output [7:0] dout
    );
endmodule