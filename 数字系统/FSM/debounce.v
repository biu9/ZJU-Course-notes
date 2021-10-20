`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/03/30 10:30:01
// Design Name: 
// Module Name: debounce
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


module debounce(reset,clk,noisy,clean);
 input reset,clk,noisy;
 output clean;
 
 parameter NDELAY = 650000;
 parameter NBITS = 20;
 
 reg [NBITS-1:0]count;
 reg xnew,clean;
 
 always @(posedge clk)
   if(reset)begin xnew <= noisy;clean <= noisy;count <= 0;end
   else if(noisy != xnew)begin xnew <= noisy;count <=0;end
   else if(count == NDELAY) clean <= xnew;
   else count <= count+1;              
endmodule
