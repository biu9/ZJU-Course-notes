//苹果产生控制模块
module Snake_Eatting_Apple
(
	input clk,
	input rst,
	
	input [6:0]head_x,
	input [6:0]head_y,
	
	output reg [6:0]apple_x,
	output reg [6:0]apple_y,

	output reg add_cube
);

	reg [31:0]clk_cnt;
	reg [10:0]random_num;
	reg [10:0]index_x;
	reg [10:0]index_y;
	
	always@(posedge clk)begin
	       index_x = index_x+1;
	       if(index_x>60)index_x = 3;
	       index_y = index_y+1;
	       if(index_y > 50)index_y = 3;
	end

	
	always@(posedge clk or negedge rst) begin
		if(!rst) begin
			clk_cnt <= 0;
			apple_x <= 24;
			apple_y <= 34;
			add_cube <= 0;
		end
		else begin
			clk_cnt <= clk_cnt+1;
			if(clk_cnt == 250_000) begin
				clk_cnt <= 0;
				if(apple_x == head_x && apple_y == head_y) begin
					add_cube <= 1;
					//apple_x <= (random_num[10:4] > 138) ? (random_num[10:4] - 25) : (random_num[10:4] == 0) ? 1 : random_num[10:4];
					//apple_y <= (random_num[6:0] > 128) ? (random_num[6:0] - 3) : (random_num[6:0] == 0) ? 1:random_num[6:0];
					apple_x <= index_x;
					apple_y <= index_y;
				end   //判断随机数是否超出频幕坐标范围 将随机数转换为下个苹果的X Y坐标
				else
					add_cube <= 0;
			end
		end
	end
endmodule