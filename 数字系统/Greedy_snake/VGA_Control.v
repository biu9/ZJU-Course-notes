// VGA控制模块  根据当前扫描到的点是哪一部分输出相应颜色
module VGA_Control
(
	input clk,
	input rst,
	
	input [1:0]snake,
	input [6:0]apple_x,
	input [6:0]apple_y,
	output reg[9:0]x_pos,
	output reg[9:0]y_pos,	
	output reg hsync,
	output reg vsync,
	output reg [11:0] color_out,
	
	input [1:0]snake_1,
    input [5:0]apple_x_1,
    input [4:0]apple_y_1,
    output reg[9:0]x_pos_1,
    output reg[9:0]y_pos_1,
    
    output reg light_test,
    
    output reg hit_flag_1,
    output reg hit_flag_2
);

	reg [19:0]clk_cnt;
	reg [9:0]line_cnt;
	reg clk_25M;
	
	localparam NONE = 2'b00;
	localparam HEAD = 2'b01;
	localparam BODY = 2'b10;
	localparam WALL = 2'b11;
	
	localparam HEAD_COLOR = 12'b0000_1111_0000;
	localparam BODY_COLOR = 12'b0000_1111_1111;
	
	
	reg [3:0]lox;
	reg [3:0]loy;
	
	reg [3:0]lox_1;
	reg [3:0]loy_1;
		
	always@(posedge clk or negedge rst) begin
		if(rst) begin
			clk_cnt <= 0;
			line_cnt <= 0;
			hsync <= 1;
			vsync <= 1;
			hit_flag_1 <= 0;
			hit_flag_2 <= 0;
			//light_test = ~light_test;
		end
		else begin
		    x_pos <= clk_cnt -110;
			y_pos <= line_cnt - 33;	  
			x_pos_1 <= clk_cnt -110;
            y_pos_1 <= line_cnt - 33;    
			if(clk_cnt == 0) begin
			    hsync <= 0;
				clk_cnt <= clk_cnt + 1;
            end
			else if(clk_cnt == 96) begin
				hsync <= 1;
				clk_cnt <= clk_cnt + 1;
            end
			else if(clk_cnt == 799) begin
				clk_cnt <= 0;
				line_cnt <= line_cnt + 1;
			end
			else clk_cnt <= clk_cnt + 1;
			
			if(line_cnt == 0) begin
				vsync <= 0;
            end
			else if(line_cnt == 2) begin
				vsync <= 1;
			end
			else if(line_cnt == 524) begin
				line_cnt <= 0;
				vsync <= 0;
			end

			if((x_pos >= 0 && x_pos < 640 && y_pos >= 0 && y_pos < 480)) begin
			    lox = x_pos[3:0];
				loy = y_pos[3:0];		
				if(x_pos[9:3] == apple_x && y_pos[9:3] == apple_y)begin
					case({loy,lox})
						8'b0000_0000:color_out = 12'b0000_0000_0000;
						default:color_out = 12'b0000_1111_0000;
					endcase
					end
				else if(snake_1 == NONE || snake_1 == WALL || snake_1 == BODY || snake_1 == HEAD || snake == NONE || snake == WALL || snake == BODY || snake == HEAD)begin
				     if(snake_1 == NONE)begin
				        if(snake == NONE)
                            color_out = 12'b0000_0000_0000;
                        if(snake == WALL)
                            color_out = 12'b0000_0000_1111;
                        if(snake == BODY)
                            color_out = 12'b0000_1111_1111;
                        if(snake == HEAD)
                            color_out = 12'b0000_1111_0000;
				     end
				     if(snake_1 == WALL)begin
				        if(snake == NONE)
                            color_out = 12'b0000_0000_1111;
                        if(snake == WALL)
                            color_out = 12'b0000_0000_1111;
                        if(snake == BODY)
                            color_out = 12'b0000_1111_1111;
                        if(snake == HEAD)
                            color_out = 12'b0000_1111_0000;
				     end
				     if(snake_1 == BODY)begin
				        if(snake == NONE)
                            color_out = 12'b0000_1111_1111;
                        if(snake == WALL)
                            color_out = 12'b0000_0000_1111;
                        if(snake == BODY)begin
                            color_out = 12'b0000_1111_1111;
                            hit_flag_1 = 1;
                            end
                        if(snake == HEAD)begin
                            color_out = 12'b0000_1111_0000;
                            hit_flag_1 = 1;
                            end
				     end
				     if(snake_1 == HEAD)begin
				        if(snake == NONE)
                            color_out = 12'b0000_1111_0000;
                        if(snake == WALL)
                            color_out = 12'b0000_0000_1111;
                        if(snake == BODY)begin
                            color_out = 12'b0000_1111_1111;
                            hit_flag_2 = 1;
                            end
                        if(snake == HEAD)begin
                            color_out = 12'b0000_1111_0000;
                            hit_flag_2 = 1;
                            end
				     end
				end	
			end
		    else
			    color_out = 12'b0000_0000_1111;
		end
		end
endmodule