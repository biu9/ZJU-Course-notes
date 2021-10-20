`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/27 15:35:39
// Design Name: 
// Module Name: clkdiv
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module clkdiv(clk,reset);
        input   clk;
        input   reset;
        
        reg [28:0] cnt;
        
        always @(posedge clk , negedge reset)
            begin
                if(!reset)
                    cnt <=0;
                else if(cnt == 29'b1000000000000)  
                    cnt <= 29'b0;
                else
                    cnt <= cnt+1;
            end
endmodule
