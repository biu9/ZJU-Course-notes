`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/03/30 11:06:59
// Design Name: 
// Module Name: lock
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


module lock (input clk,reset_in,b0_in,b1_in,
output out,
output [3:0] hex_display
);

wire reset,b0,b1;
button b_reset(clk,0,reset_in,reset);
button b_0(clk,0,b0_in,b0);
button b_1(clk,0,b1_in,b1);

parameter s_reset = 3'b000;
parameter s_0 = 3'b001;
parameter s_01 = 3'b010;
parameter s_010 = 3'b011;
parameter s_0101 = 3'b100;
parameter s_01011 = 3'b101;

reg [2:0] state,next_state;
always @(*) begin
    if(reset) begin
        next_state = s_reset;
    end
    else case (state)
    s_reset : next_state = b0 ? s_0  : b1 ? s_reset : state;
    s_0  :    next_state = b0 ? s_0  : b1 ? s_01    : state;
    s_01 :    next_state = b0 ? s_010: b1 ? s_reset : state;
    s_010:    next_state = b0 ? s_0  : b1 ? s_0101    : state; 
    s_0101  :    next_state = b0 ? s_010  : b1 ? s_01011    : state;   
    s_01011  :    next_state = b0 ? s_0  : b1 ? s_reset    : state; 
    default : next_state = s_reset;
    endcase 
end
always @(posedge clk) begin
    state <= next_state;
end
assign out = (state == s_01011);
assign hex_display = {1'b0,state};
endmodule //lock
