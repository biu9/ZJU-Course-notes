`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/24 13:26:38
// Design Name: 
// Module Name: speed_control
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


module speed_control(
        input unit_1,
        input unit_2,
        input unit_3,
        input unit_4,
        input clk,
        
        output reg speed_light_1,
        output reg speed_light_2,
        output reg speed_light_3,
        output reg speed_light_4,
        output reg [40:0]speed
    );
    
        always @(posedge clk)begin
                if(unit_4)begin
                    speed = 25_000_000;
                    speed_light_4 = 1;
                    speed_light_3 = 0;
                    speed_light_2 = 0;
                    speed_light_1 = 0;
                end
                else if(unit_3)begin
                    speed = 37_500_000;
                    speed_light_4 = 0;
                    speed_light_3 = 1;
                    speed_light_2 = 0;
                    speed_light_1 = 0;
                end
                else if(unit_2)begin
                    speed = 50_000_000;
                    speed_light_4 = 0;
                    speed_light_3 = 0;
                    speed_light_2 = 1;
                    speed_light_1 = 0;
                end
                else if(unit_1)begin
                    speed = 62_500_000;
                    speed_light_4 = 0;
                    speed_light_3 = 0;
                    speed_light_2 = 0;
                    speed_light_1 = 1;
                end
                
                if(unit_1 == 0 && unit_2 == 0 && unit_3 == 0 && unit_4 == 0) begin
                    speed = 12_500_000;
                    speed_light_4 = 0;
                    speed_light_3 = 0;
                    speed_light_2 = 0;
                    speed_light_1 = 0;
                end
        end
    
endmodule
