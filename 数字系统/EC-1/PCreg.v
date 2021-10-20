module PCreg(PCload,reset,clk,PC_in,PC_out);
        input   PCload;
        input   reset;
        input   [3:0]PC_in;
        input   clk;
        output  reg [3:0]PC_out;
        
        always @(negedge clk or posedge reset) begin
                if(reset) begin
                     PC_out = 0;
                end
                else if(PCload)begin
                    PC_out = PC_in;
                end
        end
endmodule