`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/25 12:02:21
// Design Name: 
// Module Name: contrl_unit
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


module Control_unit(clk,reset,IR,A,IRload,PCload,INmux,Aload,JNZmux,OutE,Halt1);

input   clk;
input   reset;
input   [2:0]IR;
input   A;

output  reg     IRload;
output  reg     PCload;
output  reg     INmux;
output  reg     Aload;
output  reg     JNZmux;
output  reg     OutE;
output  reg     Halt1;

        reg     [2:0]current_state;
        reg     [2:0]next_state;

parameter [2:0] Fetch = 3'b000,Decode = 3'b001,Input = 3'b011,Output = 3'b100,Dec = 3'b101,Jnz = 3'b110,Halt = 3'b111;

always @(posedge clk or posedge reset) begin
        if(reset)
            current_state <= Fetch;
        else
            current_state <= next_state;
end

always @(current_state or IR)begin
        case(current_state)
            Fetch: next_state = Decode;
            Decode: if(IR == 3'b011) next_state = Input;
                    else if(IR == 3'b100) next_state = Output;
                    else if(IR == 3'b101) next_state = Dec;
                    else if(IR == 3'b110) next_state = Jnz;
                    else next_state = Halt;
            default: next_state = Fetch;
        endcase
end

always @(posedge clk or posedge reset) begin
        if(reset) begin
                IRload <= 0;PCload <= 0;INmux <= 0;Aload <= 0;JNZmux <= 0;OutE <= 0;Halt1 <= 0;
        end
        else begin
                case(next_state)
                    Fetch:begin
                        IRload <= 1;PCload <= 1;INmux <= 0;Aload <= 0;JNZmux <= 0;OutE <= 0;Halt1 <= 0;
                    end
                    Decode:begin
                        IRload <= 0;PCload <= 0;INmux <= 0;Aload <= 0;JNZmux <= 0;OutE <= 0;Halt1 <= 0;
                    end
                    Input: begin
                        IRload <= 0;PCload <= 0;INmux <= 1;Aload <= 1;JNZmux <= 0;OutE <= 0;Halt1 <= 0;
                    end
                    Output: begin
                        IRload <= 0;PCload <= 0;INmux <= 0;Aload <= 0;JNZmux <= 0;OutE <= 1;Halt1 <= 0;
                    end
                    Dec: begin
                        IRload <= 0;PCload <= 0;INmux <= 0;Aload <= 1;JNZmux <= 0;OutE <= 0;Halt1 <= 0;
                    end
                    Jnz: begin
                        if(A == 1)begin
                        IRload <= 0;PCload <= 1;INmux <= 0;Aload <= 0;JNZmux <= 1;OutE <= 0;Halt1 <= 0;
                        end
                        else begin
                        IRload <= 0;PCload <= 0;INmux <= 0;Aload <= 0;JNZmux <= 1;OutE <= 0;Halt1 <= 0;
                        end
                    end
                    Halt:begin
                        IRload <= 0;PCload <= 0;INmux <= 0;Aload <= 0;JNZmux <= 0;OutE <= 0;Halt1 <= 1;
                    end
                endcase
        end
end
endmodule
