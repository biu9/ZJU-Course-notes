`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/26 20:55:19
// Design Name: 
// Module Name: Datapath
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


module Datapath(IRload,INmux,Aload,reset,clk,Input,JNZmux,PCload,IR7_5,Output,OutE,A);
        input   IRload;
        input   JNZmux;
        input   PCload;
        input   INmux;
        input   Aload;
        input   reset;
        input   clk;
        input   OutE;
        input   [7:0]Input;
        
        output  A;
        output  [7:0]Output;
        output  [2:0]IR7_5;
        
        wire    [7:0]IR_in;
        wire    [3:0]IR_out;
        wire    [3:0]mux2_1_out;
        wire    [3:0]PC_D_in;
        wire    [3:0]PC_out;
        wire    [7:0]A_in;
        wire    [7:0]mux2_2_out;
        wire    [7:0]A_out;
        
        IRreg IR1(.IRload(IRload),.reset(reset),.clk(clk),.IR_in(IR_in),.IR7_5(IR7_5),.IR_out(IR_out));
        mux2_1 m1(.IR_in(IR_out),.mux2_1_out(mux2_1_out),.JNZmux(JNZmux),.PC_in(PC_D_in));
        PCreg PC1(.PCload(PCload),.reset(reset),.clk(clk),.PC_in(mux2_1_out),.PC_out(PC_out));
        Increment I1(.Increment_in(PC_out),.Increment_out(PC_D_in));
        ROM R1(.adress(PC_out),.ROM_out(IR_in));
        mux2_2 m2(.Input(Input),.A_in(A_in),.INmux(INmux),.mux2_2_out(mux2_2_out));
        Areg A1(.Aload(Aload),.reset(reset),.clk(clk),.mux2_2_out(mux2_2_out),.A_out(A_out));
        Derement D1(.PC_in(A_out),.PC_D_out(A_in));
        Nor n1(.A_out(A_out),.Out_nor(A));
        Out o1(.A_out(A_out),.OutE(OutE),.Out(Output));
        
        

endmodule
