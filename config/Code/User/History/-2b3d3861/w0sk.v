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

// barrel_shifter8
// module top(
//         input [7:0] din,
//         input [2:0] shamt,
//         input LR,
//         input AL,
//         output [7:0] dout
//     );
//
//     barrel_shifter8 u_barrel_shifter8(
//                         .din(din),
//                         .shamt(shamt),
//                         .LR(LR),
//                         .AL(AL),
//                         .dout(dout)
//                     );
// endmodule

// LFSR
module top(
        input clk,
        input rst,
        input [7:0] in,
        output reg [7:0] out
    );

    LFSR #(.N(8)) u_LFSR (
             .clk  	( clk   ),
             .rst  	( rst   ),
             .in   	( in    ),
             .out  	( out   )
         );


endmodule
