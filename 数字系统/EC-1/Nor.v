`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/27 14:52:50
// Design Name: 
// Module Name: Nor
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


module Nor(A_out,Out_nor);
        input   [7:0]A_out;
        output  reg Out_nor;
        always @(*)begin
            if(A_out == 8'b00000000) Out_nor = 1;
            else Out_nor = 0;
        end
endmodule
