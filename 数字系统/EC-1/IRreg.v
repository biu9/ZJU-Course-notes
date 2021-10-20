module IRreg(IRload,reset,clk,IR_in,IR7_5,IR_out);
        input   [7:0]IR_in;
        input   clk;
        input   reset;
        input   IRload;
        output  reg [2:0]IR7_5;
        output  reg [3:0]IR_out;
        
        always @(negedge clk or posedge reset) begin
                if(reset) begin
                    IR7_5 = 0;
                    IR_out = 0;
                end
                else if(IRload)begin
                    IR7_5 = IR_in[7:5];
                    IR_out = IR_in[3:0];
                end
        end
endmodule