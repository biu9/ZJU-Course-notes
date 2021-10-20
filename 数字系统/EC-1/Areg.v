`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/26 23:53:14
// Design Name: 
// Module Name: Areg
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


module Areg(Aload,reset,clk,mux2_2_out,A_out);
        input   Aload;
        input   reset;
        input   clk;
        input   [7:0]mux2_2_out;
        output  reg [7:0]A_out;
        
        always @(negedge clk or posedge reset) begin
                if(reset) begin
                    A_out = 0;
                end
                else if(Aload)begin
                    A_out = mux2_2_out;
                end
        end

endmodule
