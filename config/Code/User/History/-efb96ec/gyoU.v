`timescale 1ns/1ns

module alu_tb;

    // Parameters
    parameter WIDTH = 4; // ALU 输入和输出的位宽

    // Intergers
    integer i, j;

    // Inputs
    reg [2:0] op;
    reg in_c;
    reg [WIDTH-1:0] in_x;
    reg [WIDTH-1:0] in_y;

    // Outputs
    wire [WIDTH-1:0] out_s;
    wire out_c;
    wire zero;
    wire overflow;

    // Instantiate the ALU module
    alu uut (
            .op(op),
            .in_c(in_c),
            .in_x(in_x),
            .in_y(in_y),
            .out_s(out_s),
            .out_c(out_c),
            .zero(zero),
            .overflow(overflow)
        );

    task check;  //测试任务
        input [3:0] results;  //ALU的结果预期正确输出
        input resultof, resultc, resultz;  //ALU的预期溢出，进位，零位
        begin
            if(out_s!=results)  //比较预期结果和测试单元输出的outputs
            begin               //出错时显示
                $display("Error:x=%h,y=%h,ctrl=%b,s should be %h, get %h", in_x, in_y, op, results, out_s);
            end
            //自行添加溢出，进位和零位的比较
            if(overflow!=resultof)  //比较预期结果和测试单元输出的outputs
            begin               //出错时显示
                $display("Error:x=%h,y=%h,ctrl=%b,overflow should be %b, get %b", in_x, in_y, op, resultof, overflow);
            end
            if(out_c!=resultc)  //比较预期结果和测试单元输出的outputs
            begin               //出错时显示
                $display("Error:x=%h,y=%h,ctrl=%b,cout should be %b, get %b", in_x, in_y, op, resultc, out_c);
            end
            if(zero!=resultz)  //比较预期结果和测试单元输出的outputs
            begin               //出错时显示
                $display("Error:x=%h,y=%h,ctrl=%b,zero should be %b, get %b", in_x, in_y, op, resultz, zero);
            end
        end
    endtask

    // Test stimulus
    initial begin
        // Reset
        in_c = 0;
        in_x = 0;
        in_y = 0;

        // Test cases
        $display("Starting ALU test...");
        // format off
        op = 0;
        in_x = 4'b0001;
        in_y = 4'b0001;

        #20 check(4'b0010, 0, 0, 0);


        // End of test
        $display("ALU test complete.");
        $finish;
    end

endmodule
