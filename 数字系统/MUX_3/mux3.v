`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/03/29 20:06:30
// Design Name: 
// Module Name: mux3
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

module mux3(
    input a,
    input b,
    input c,
    input [1:0] s,
    output reg r
    );
    always@(*)
    begin
    if (s == 2'b00) r =a;
    else if (s == 2'b01) r =b;
    else if (s == 2'b10) r =c;
    else r = 4'bX;
    end
endmodule

