`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/17 14:28:26
// Design Name: 
// Module Name: clk_2ms
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


module clk_2ms(
    input clk,
    input rst,
    output reg clk_2ms
    );
    
    parameter COUNT = 100_000;
    reg [19:0] cnt;
    
    always@(posedge clk or posedge rst) begin
      if(rst) cnt <= 0;
      else if(cnt == COUNT) begin
        clk_2ms <= ~clk_2ms;
        cnt <= 0;
      end
      else if(cnt < COUNT) cnt <= cnt +1;
      else cnt <= 0;
    end
endmodule