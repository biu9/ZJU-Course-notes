`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/17 14:28:58
// Design Name: 
// Module Name: clk_1s
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


module clk_1s(
    input clk,
    input rst,
    output reg clk_1s
    );
    
    parameter COUNT = 50_000_000;
    reg [28:0] cnt;
    
    always@(posedge clk or posedge rst)begin
      if(rst) cnt <= 0;
      else if(cnt == COUNT) begin
        clk_1s <= ~clk_1s;
        cnt <= 0;
      end
      else if(cnt < COUNT) cnt <= cnt + 1;
      else cnt <= 0;
    end
endmodule
