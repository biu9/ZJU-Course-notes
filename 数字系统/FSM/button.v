`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/03/31 23:46:16
// Design Name: 
// Module Name: button
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


module button(input clk,reset,button_in,
output reg light
    );
  reg button,btemp;
  always @(posedge clk)
    {button,btemp} <= {btemp,button_in};
  wire clean;
  debounce db1(.clk(clk),.reset(reset),.noisy(button_in),.clean(clean));
  reg old_bpressed;
  always @(posedge clk)begin
    if (reset)
      begin light <= 0; old_bpressed <= 0; end
    else if(old_bpressed == 0 && clean == 1)
      light <= 1;
    else
      light <= 0;
   old_bpressed <= clean;
    end
endmodule
