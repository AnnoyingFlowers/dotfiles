module mux21a(
        input [1:0]  a,
        input s,
        output  y
    );

    MuxKeyWithDefault #(2, 1, 1) i0 (y, s, 1'b0, {
                                         1'b0, a[0],
                                         1'b1, a[1]
                                     });
endmodule
