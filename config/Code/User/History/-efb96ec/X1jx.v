module alu_tb;

    // Parameters
    parameter WIDTH = 4; // ALU 输入和输出的位宽

    // Intergers
    integer i, j;

    // Inputs
    reg [2:0] op;
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
                $display("Error:x=%b,y=%b,ctrl=%b,s should be %b, get %b", in_x, in_y, op, results, out_s);
            end
            //自行添加溢出，进位和零位的比较
            if(overflow!=resultof)  //比较预期结果和测试单元输出的outputs
            begin               //出错时显示
                $display("Error:x=%b,y=%b,ctrl=%b,overflow should be %b, get %b", in_x, in_y, op, resultof, overflow);
            end
            if(out_c!=resultc)  //比较预期结果和测试单元输出的outputs
            begin               //出错时显示
                $display("Error:x=%b,y=%b,ctrl=%b,cout should be %b, get %b", in_x, in_y, op, resultc, out_c);
            end
            if(zero!=resultz)  //比较预期结果和测试单元输出的outputs
            begin               //出错时显示
                $display("Error:x=%b,y=%b,ctrl=%b,zero should be %b, get %b", in_x, in_y, op, resultz, zero);
            end
        end
    endtask

    // Test stimulus
    initial begin
        // Reset
        in_x = 0;
        in_y = 0;

        // Test cases
        $display("Starting ALU test...");

        op = 0;
        in_x = 4'b0001;
        in_y = 4'b0001;
        #20 check(4'b0010, 0, 0, 0);

        in_x = 4'b0111;
        in_y = 4'b0001;
        #20 check(4'b1000, 1, 0, 0);

        in_x = 4'b0000;
        in_y = 4'b0000;
        #20 check(4'b0000, 0, 0, 1);

        in_x = 4'b0011;
        in_y = 4'b1101;
        #20 check(4'b0000, 0, 1, 1);

        op = 1;
        in_x = 4'b1000;
        in_y = 4'b0001;
        #20 check(4'b0111, 1, 1, 0);

        in_x = 4'b1000;
        in_y = 4'b0000;
        #20 check(4'b1000, 0, 0, 0);

        in_x = 4'b1000;
        in_y = 4'b1111;
        #20 check(4'b1001, 0, 0, 0);

        in_x = 4'b0111;
        in_y = 4'b1111;
        #20 check(4'b1000, 1, 0, 0);

        op = 2;
        in_x = 4'b1100;
        in_y = 4'b0001;
        #20 check(4'b0011, 0, 0, 0);

        op = 3;
        in_x = 4'b1100;
        in_y = 4'b0011;
        #20 check(4'b0000, 0, 0, 1);

        op = 4;
        in_x = 4'b1100;
        in_y = 4'b0011;
        #20 check(4'b1111, 0, 0, 0);

        op = 5;
        in_x = 4'b0101;
        in_y = 4'b0101;
        #20 check(4'b0000, 0, 0, 1);

        op = 6;
        in_x = 4'b1000;
        in_y = 4'b0000;
        #20 check(4'b0001, 0, 0, 1);

        in_x = 4'b0000;
        in_y = 4'b1111;
        #20 check(4'b0000, 0, 0, 0);

        // End of test
        $display("ALU test complete.");
        $finish;
    end

endmodule
