//����ģ��
//6.22 10:55 �޸���x_pos��y_pos�������ǵ��߿��9�ĵ���12��Ϊ����ͼ�����һ������֮��֮���޷��Ե�ƻ��������
//6.22 11:02 �ָĻ����ˣ�ò�Ƹĵ�12û�н�����⣬��������һ��ʼ��ƻ��Ҳ����ʾ��
//6.22 11:14 ò�ƺ�x_posû�й�ϵ
//6.22 11:35 Ӧ�ú�head_x�й�ϵ�������޸���head�ĸ�ֵ��ʽ���ӷ�������ֵ�ĳ���������ֵ���ĵ���assign���
//6.22 11:41 ��;ֹͣ���ۺϣ��о�Ӧ�ú�apple_x�йأ������޸���apple�ĳ�ʼ���꣬�������ܲ��ܱ��Ե�
//6.22 11:58 Ӧ�ú�apple�������й�ϵ
//6.22 12:01 ע�͵���������������䣬�ĳ���++�����в���
//6.24 13:22 �޸ĵڶ�����
//6.24 13:58 д��һ���ٶȿ���ģ�飬��snakeģ�������speed����top�������light����ʾ��ǰ�ٶ�
//6.24 14:16 ò����speed���߿�̫С�����������һֱ�˶��ĺܿ죬���ڰ��߿�ĳ�29�����ٱ�ɼ��٣����в���
//6.24 14:24 ����˸ı��ٶȣ������²����ֲ���ȥ֮���߾ͻ᲻����Ŀǰ��speed_control������ĸ����붼����0ʱ����жϸ���һ��
//6.24 14:40 û��Ч���������ٴ��޸��߿���29�ĵ�40�����в���
//6.24 14:46 ò��������߿����ƣ��ĵ���31�����в���
//6.24 15:01 ò�Ʋ����߿�����ƣ�ò���ǰ�always @(posedge clk)�ĳ�always @(*)������
//6.26 15:51 ������������ײ���жϣ�Ŀǰ���ж�д����vga_controlģ����
//6.26 16:00 ò�Ʒ����ض���Ĵ���������vga_control��д��hit_flag������ж��Ƿ���ײ
//6.26 16:08 �������Գɹ�����ײ��һ���Ժ��߼�ʹ����reset��Ҳ�����ٶ����²�����Ϊhit_flagû����0������vga_control�������0
//6.26 16:58 ��hit_flag�ĳ���hit_flag_1��hit_flag_2���ж���˭��ײ��˭����ʼ����

module top
(
    input clk,
	input rst,
	
	input left,
	input right,
	input up,
	input down,

	input left_1,
	input right_1,
	input up_1,
	input down_1,
	
	//------------------------�����ߵ��ٶ�
	input unit_1,
	input unit_2,
	input unit_3,
	input unit_4,
	
	output speed_light_1,
    output speed_light_2,
    output speed_light_3,
    output speed_light_4, 
    
	//---------------------------------------
	
	output hsync,
	output vsync,
	output [11:0]color_out,
	
	output light_test,
	
	output [3:0] sel,
    output [7:0] seg
);

	wire left_key_press;
	wire right_key_press;
	wire up_key_press;
	wire down_key_press;
	
    wire left_key_press_1;
    wire right_key_press_1;
    wire up_key_press_1;
    wire down_key_press_1;
    
	wire [1:0]snake;
	wire [9:0]x_pos;
	wire [9:0]y_pos;
	wire [6:0]apple_x;
	wire [6:0]apple_y;
	wire [6:0]head_x;
	wire [6:0]head_y;
	
	wire add_cube;
	wire[1:0]game_status;
	wire hit_wall;
	wire hit_body;
	wire die_flash;
	wire restart;
	wire [6:0]cube_num;
	
	wire rst_n;
	
	wire [1:0]snake_1;
    wire [9:0]x_pos_1;
    wire [9:0]y_pos_1;
    wire [3:0]apple_x_1;
    wire [3:0]apple_y_1;
    wire [5:0]head_x_1;
    wire [5:0]head_y_1;
    
    wire add_cube_1;
    wire[1:0]game_status_1;
    wire hit_wall_1;
    wire hit_body_1;
    wire die_flash_1;
    wire restart_1;
    wire [6:0]cube_num_1;
    
    wire over;
    
    wire [40:0] speed;//-----------------------------------------------�ߵ��ٶ�
    
    wire hit_flag_1;
    wire hit_flag_2;
    
	assign rst_n = ~rst;
	
	speed_control sp1(
	   .clk(clk),
	   .unit_1(unit_1),
	   .unit_2(unit_2),
	   .unit_3(unit_3),
	   .unit_4(unit_4),
	   .speed(speed),
	   .speed_light_1(speed_light_1),
	   .speed_light_2(speed_light_2),
	   .speed_light_3(speed_light_3),
	   .speed_light_4(speed_light_4)
	);

    Game_Ctrl_Unit U1 (
        .clk(clk),
	    .rst(rst_n),
	    .key1_press(left_key_press),
	    .key2_press(right_key_press),
	    .key3_press(up_key_press),
	    .key4_press(down_key_press),
        .game_status(game_status),
		.hit_wall(hit_wall),
		.hit_body(hit_body),
		.die_flash(die_flash),
		.restart(restart)		
	);
	
	Snake_Eatting_Apple U2 (
        .clk(clk),
		.rst(rst_n),
		.apple_x(apple_x),
		.apple_y(apple_y),
		.head_x(head_x),
		.head_y(head_y),
		.add_cube(add_cube)	
	);
	
	Snake U3 (
	    .clk(clk),
		.rst(rst_n),
		.left_press(left_key_press),
		.right_press(right_key_press),
		.up_press(up_key_press),
		.down_press(down_key_press),
		.snake(snake),
		.x_pos(x_pos),
		.y_pos(y_pos),
		.head_x(head_x),
		.head_y(head_y),
		.add_cube(add_cube),
		.game_status(game_status),
		.cube_num(cube_num),
		.hit_body(hit_body),
		.hit_wall(hit_wall),
		.die_flash(die_flash),
		
		.speed(speed),
		.hit_flag_1(hit_flag_1),
		
		.over(over)//-----------------------------------------------
	);

	VGA_top U4 (
		.clk(clk),
		.rst(rst),
		.hsync(hsync),
		.vsync(vsync),
		.snake(snake),
        .color_out(color_out),
		.x_pos(x_pos),
		.y_pos(y_pos),
		.apple_x(apple_x),
		.apple_y(apple_y),
		.x_pos_1(x_pos_1),
        .y_pos_1(y_pos_1),
        //.apple_x_1(apple_x_1),
        //.apple_y_1(apple_y_1),
        .snake_1(snake_1),
        .light_test(light_test),
        .hit_flag_1(hit_flag_1),
        .hit_flag_2(hit_flag_2)
	);
	
	Key U5 (
		.clk(clk),
		.rst(rst_n),
		.left(left),
		.right(right),
		.up(up),
		.down(down),
		.left_key_press(left_key_press),
		.right_key_press(right_key_press),
		.up_key_press(up_key_press),
		.down_key_press(down_key_press)		
	);
	
		Key U6 (
        .clk(clk),
        .rst(rst_n),
        .left(left_1),
        .right(right_1),
        .up(up_1),
        .down(down_1),
        .left_key_press(left_key_press_1),
        .right_key_press(right_key_press_1),
        .up_key_press(up_key_press_1),
        .down_key_press(down_key_press_1)        
    );
  //---------------------------------------------------------------------  
        Game_Ctrl_Unit U1_1 (
        .clk(clk),
        .rst(rst_n),
        .key1_press(left_key_press_1),
        .key2_press(right_key_press_1),
        .key3_press(up_key_press_1),
        .key4_press(down_key_press_1),
        .game_status(game_status_1),
        .hit_wall(hit_wall_1),
        .hit_body(hit_body_1),
        .die_flash(die_flash_1),
        .restart(restart_1)        
    );
    /*
    Snake_Eatting_Apple U2_1 (
        .clk(clk),
        .rst(rst_n),
        .apple_x(apple_x_1),
        .apple_y(apple_y_1),
        .head_x(head_x_1),
        .head_y(head_y_1),
        .add_cube(add_cube_1)    
    );
    */
    Snake_1 U3_1 (
        .clk(clk),
        .rst(rst_n),
        .left_press(left_key_press_1),
        .right_press(right_key_press_1),
        .up_press(up_key_press_1),
        .down_press(down_key_press_1),
        .snake(snake_1),
        .x_pos(x_pos),
        .y_pos(y_pos),
        .head_x(head_x_1),
        .head_y(head_y_1),
       // .add_cube(add_cube_1),
        .game_status(game_status_1),
        .cube_num(cube_num_1),
        .hit_body(hit_body_1),
        .hit_wall(hit_wall_1),
        .die_flash(die_flash_1),
        
        .speed(speed),
        .hit_flag_2(hit_flag_2),
        
        .over(over)//--------------------------------------------------------------------
    );
    
        counter U7(
        .clk(clk),
        .rst(rst),
        .over(over),
        .sel(sel),
        .seg(seg)
   );    

endmodule
