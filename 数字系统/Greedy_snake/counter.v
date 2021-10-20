`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/17 14:29:45
// Design Name: 
// Module Name: counter
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


module counter(
    input clk,
    input rst,
    output over,
    output [3:0] sel,
    output [7:0] seg
    );
    
    wire clk_1s, clk_2ms;
    clk_1s u1(clk,rst,clk_1s);
    clk_2ms u2(clk,rst,clk_2ms);
    
    wire [7:0] q;
    cnt60 u3(clk_1s,rst,q,over);
    scan u4(clk_2ms,q,seg,sel);
endmodule
