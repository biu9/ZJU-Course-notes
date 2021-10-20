`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/17 14:27:14
// Design Name: 
// Module Name: scan
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


module scan(
    input clk,
    input [7:0] q,
    output reg [7:0] seg,
    output reg [3:0] sel
    ); // 数码管的扫描输出模块，实地化时需要连接clk_2ms时钟信号
    
    reg [1:0] d; // 用于选择某一个数码管
    reg [3:0] data; // 用于接收数码管输出的数据
    
    always@(posedge clk) begin
      if(d == 2'b11) d <= 2'b00;
      else d <= d + 1;
    end // 当选择最后一段数码管时，下一次将选择第一段；否则下一次将选择下一段数码管
    
    always@(posedge clk) begin
      case(d)
        2'b00: sel <= 4'b0111; // 选择第一段数码管
        2'b01: sel <= 4'b1011; // 选择第二段数码管
        2'b10: sel <= 4'b1101; // 选择第三段数码管
        2'b11: sel <= 4'b1110; // 选择第四段数码管
        default sel <= 4'b1110;
      endcase

      case(d)
        2'b00: data <= 4'bzzzz;
        2'b01: data <= 4'bzzzz;
        2'b10: data <= q[7:4]; // 数码管第三段输出十位数
        2'b11: data <= q[3:0]; // 数码管第四段输出个位数
      endcase
    end
    
    always@(data) begin // 数码管的BCD译码
      case(data)
        4'b0000: seg <= 8'b0000_0011;
        4'b0001: seg <= 8'b1001_1111;
        4'b0010: seg <= 8'b0010_0101;
        4'b0011: seg <= 8'b0000_1101;
        4'b0100: seg <= 8'b1001_1001;
        4'b0101: seg <= 8'b0100_1001;
        4'b0110: seg <= 8'b0100_0001;
        4'b0111: seg <= 8'b0001_1111;
        4'b1000: seg <= 8'b0000_0001;
        4'b1001: seg <= 8'b0000_1001;
        default seg <= 8'b1111_1111;
      endcase  
    end
endmodule