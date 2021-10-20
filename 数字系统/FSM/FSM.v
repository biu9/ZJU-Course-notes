`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/03/30 10:20:08
// Design Name: 
// Module Name: FSM
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

module FSM (
input clk,reset_in,b0,b1,
output out,
output reg[11:0]segment
);
wire [3:0] hex_display;

lock l1(.clk(clk),.hex_display(hex_display),.reset_in(reset_in),.b0_in(b0),.b1_in(b1),.out(out));
always @(*)begin
if(hex_display == 0)
segment = 12'b011100000011;
else if(hex_display == 1)
segment = 12'b011110011111;
else if(hex_display == 2)
segment = 12'b011100100101;
else if(hex_display == 3)
segment = 12'b011100001101;
else if(hex_display == 4)
segment = 12'b011110011001;
else
segment = 12'b011101001001;
end
endmodule //FSM
