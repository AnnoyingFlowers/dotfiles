module key2ascii(
        input [7:0] data,
        output [7:0] ascii
    );
    MuxKeyWithDefault #(37, 8, 8) LUT (.out(ascii), .key(data), .default_out(8'b0), .lut({
                                           8'hF0, 8'hF0,

                                           8'h16, 8'h31,
                                           8'h1E, 8'h32,
                                           8'h26, 8'h33,
                                           8'h25, 8'h34,
                                           8'h2E, 8'h35,
                                           8'h36, 8'h36,
                                           8'h3D, 8'h37,
                                           8'h3E, 8'h38,
                                           8'h46, 8'h39,
                                           8'h45, 8'h30,

                                           8'h1C, 8'h61,
                                           8'h32, 8'h62,
                                           8'h21, 8'h63,
                                           8'h23, 8'h64,
                                           8'h24, 8'h65,
                                           8'h2B, 8'h66,
                                           8'h34, 8'h67,
                                           8'h33, 8'h68,
                                           8'h43, 8'h69,
                                           8'h3B, 8'h6A,
                                           8'h42, 8'h6B,
                                           8'h4B, 8'h6C,
                                           8'h3A, 8'h6D,
                                           8'h31, 8'h6E,
                                           8'h44, 8'h6F,
                                           8'h4D, 8'h70,
                                           8'h15, 8'h71,
                                           8'h2D, 8'h72,
                                           8'h1B, 8'h73,
                                           8'h2C, 8'h74,
                                           8'h3C, 8'h75,
                                           8'h2A, 8'h76,
                                           8'h1D, 8'h77,
                                           8'h22, 8'h78,
                                           8'h35, 8'h79,
                                           8'h1A, 8'h7A
                                       }));
endmodule
