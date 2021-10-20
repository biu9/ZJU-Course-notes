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
    ); // ����ܵ�ɨ�����ģ�飬ʵ�ػ�ʱ��Ҫ����clk_2msʱ���ź�
    
    reg [1:0] d; // ����ѡ��ĳһ�������
    reg [3:0] data; // ���ڽ�����������������
    
    always@(posedge clk) begin
      if(d == 2'b11) d <= 2'b00;
      else d <= d + 1;
    end // ��ѡ�����һ�������ʱ����һ�ν�ѡ���һ�Σ�������һ�ν�ѡ����һ�������
    
    always@(posedge clk) begin
      case(d)
        2'b00: sel <= 4'b0111; // ѡ���һ�������
        2'b01: sel <= 4'b1011; // ѡ��ڶ��������
        2'b10: sel <= 4'b1101; // ѡ������������
        2'b11: sel <= 4'b1110; // ѡ����Ķ������
        default sel <= 4'b1110;
      endcase

      case(d)
        2'b00: data <= 4'bzzzz;
        2'b01: data <= 4'bzzzz;
        2'b10: data <= q[7:4]; // ����ܵ��������ʮλ��
        2'b11: data <= q[3:0]; // ����ܵ��Ķ������λ��
      endcase
    end
    
    always@(data) begin // ����ܵ�BCD����
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