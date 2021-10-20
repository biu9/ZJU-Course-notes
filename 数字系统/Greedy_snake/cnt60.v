`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/06/17 14:27:52
// Design Name: 
// Module Name: cnt60
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


module cnt60(
    input clk,
    input rst,
    output reg [7:0] q, // q[7:4]���ڴ��浹��ʱ��ʮλ����q[3:0]���ڴ��浹��ʱ�ĸ�λ��
    output reg over // ʱ�䵽����Ϸ����
    ); // ����ģ�飬ģ��ʵ�ػ�ʱ��Ҫ����clk_1sʱ��
    
    always@(posedge clk or posedge rst) begin
      if(rst) begin
      q <= 8'b0110_0000; // ��ʱ�������ʾ60
      // �޸���������Խ���Ϸʱ�����Ϊ�Լ���Ҫ��ʱ��
      over <= 1'b0;
      end
      else if(q[3:0] == 0 && q[7:4] != 0) begin // �����λΪ0��ʮλ��Ϊ0�����λ����9��ʮλ����1
        q[7:4] <= q[7:4] - 1;
        q[3:0] <= q[3:0] + 9;
      end
      else if(q == 8'b0000_0000)begin // �����λΪ0��ʮλҲΪ0���򱣳�ԭ״
        q <= 8'b0000_0000;
        over <= 1'b1;
      end
      else begin // ��λ��Ϊ0����ʮλ�����䣬��λ����1
        q[3:0] <= q[3:0] - 1;
      end
    end
endmodule