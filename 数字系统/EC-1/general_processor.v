`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/26 20:51:37
// Design Name: 
// Module Name: general_processor
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

module general_processor(clk,reset,Input,Output);
        input   clk;
        input   reset;
        input   [7:0]Input;
        output  [7:0]Output;

        wire    [2:0]IR7_5;
        wire    A;
        wire    IRload;
        wire    PCload;
        wire    INmux;
        wire    Aload;
        wire    JNZmux;
        wire    OutE;
        wire    Halt;
        
        //clkdiv c1(clk,reset);
        Control_unit c2(.clk(clk),.reset(reset),.IR(IR7_5),.A(A),.IRload(IRload),.PCload(PCload),.INmux(INmux),.Aload(Aload),.JNZmux(JNZmux),.OutE(OutE),.Halt1(Halt));
        Datapath d1(.IRload(IRload),.PCload(PCload),.reset(reset),.clk(clk),.INmux(INmux),.Aload(Aload),.Input(Input),.IR7_5(IR7_5),.Output(Output),.OutE(OutE),.A(A),.JNZmux(JNZmux));
endmodule
