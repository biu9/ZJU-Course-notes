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
    output reg [7:0] q, // q[7:4]用于储存倒计时的十位数，q[3:0]用于储存倒计时的个位数
    output reg over // 时间到，游戏结束
    ); // 计数模块，模块实地化时需要调用clk_1s时钟
    
    always@(posedge clk or posedge rst) begin
      if(rst) begin
      q <= 8'b0110_0000; // 此时数码管显示60
      // 修改这个数可以将游戏时间调整为自己想要的时间
      over <= 1'b0;
      end
      else if(q[3:0] == 0 && q[7:4] != 0) begin // 如果个位为0，十位不为0，则个位数加9，十位数减1
        q[7:4] <= q[7:4] - 1;
        q[3:0] <= q[3:0] + 9;
      end
      else if(q == 8'b0000_0000)begin // 如果个位为0，十位也为0，则保持原状
        q <= 8'b0000_0000;
        over <= 1'b1;
      end
      else begin // 个位不为0，则十位数不变，个位数减1
        q[3:0] <= q[3:0] - 1;
      end
    end
endmodule