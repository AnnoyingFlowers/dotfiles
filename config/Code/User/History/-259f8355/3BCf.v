module pri_encode83(x,en,idc,y);
    input  [7:0] x;
    input  en;
    output idc;
    output reg [2:0]y;
    integer i;

    assign idc = (x != 8'b00000000 && en) ? 1'b1 : 1'b0;
    ///////////////////////////////////////////
    // 普通版本
    // always @(x or en) begin
    //     if (en) begin
    //         y = 0;
    //         for( i = 0; i <= 7; i = i+1) begin
    //             if(x[i] == 1) begin
    //                 y = i[2:0];
    //             end
    //         end
    //     end
    //     else
    //         y = 0;
    // end
    ///////////////////////////////////////////
    // casez版本（verilator建议我用casez而不是casex，好吧，那就casez吧）
    // case语句的表达式的值有4中情况：0、1、z、x。4种是不同的，故表达式要严格的相等才可以操作分支语句。
    // casez语句中的表达式情况有三种：0、1、x。不用关心z，z可以和任何数值相等，即z =0.z= 1,z=x;
    // casex语句的表达式情况有二种：0、1.不用关心x和z。即x=z=0,x=z=1.
    always @ (*) begin
        casez({en, x})
            9'b11zzzzzzz:
                y = 3'b111;
            9'b101zzzzzz:
                y = 3'b110;
            9'b1001zzzzz:
                y = 3'b101;
            9'b10001zzzz:
                y = 3'b100;
            9'b100001zzz:
                y = 3'b011;
            9'b1000001zz:
                y = 3'b010;
            9'b10000001z:
                y = 3'b001;
            9'b100000001:
                y = 3'b000;
            default:
                y = 3'b000;
            endcasez
        end
    endmodule
