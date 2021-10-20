`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/26 20:55:04
// Design Name: 
// Module Name: clk_500ms
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


module clk_500ms(clk);
        input   clk;
        reg [29:0]cnt;
        always @(posedge clk)begin
            if(cnt == 100000000)begin
                
            end
        end
endmodule
