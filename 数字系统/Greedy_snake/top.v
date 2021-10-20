//顶层模块
//6.22 10:55 修改了x_pos和y_pos，把他们的线宽从9改到了12，为了试图解决到一定坐标之外之后无法吃到苹果的问题
//6.22 11:02 又改回来了，貌似改到12没有解决问题，反而导致一开始的苹果也不显示了
//6.22 11:14 貌似和x_pos没有关系
//6.22 11:35 应该和head_x有关系，现在修改了head的赋值方式，从非阻塞赋值改成了阻塞赋值，改掉了assign语句
//6.22 11:41 中途停止了综合，感觉应该和apple_x有关，现在修改了apple的初始坐标，以试验能不能被吃掉
//6.22 11:58 应该和apple的坐标有关系
//6.22 12:01 注释掉了随机坐标产生语句，改成了++，进行测试
//6.24 13:22 修改第二条蛇
//6.24 13:58 写了一个速度控制模块，在snake模块里加了speed，在top里面加了light以显示当前速度
//6.24 14:16 貌似是speed的线宽太小导致溢出，蛇一直运动的很快，现在把线宽改成29，加速变成减速，进行测试
//6.24 14:24 完成了改变速度，但按下拨码又拨回去之后蛇就会不动，目前把speed_control里对于四个拨码都等于0时候的判断改了一下
//6.24 14:40 没有效果，现在再次修改线宽，从29改到40，进行测试
//6.24 14:46 貌似有最大线宽限制，改到了31，进行测试
//6.24 15:01 貌似不是线宽的限制，貌似是把always @(posedge clk)改成always @(*)的问题
//6.26 15:51 制作两条蛇碰撞的判断，目前把判断写在了vga_control模块里
//6.26 16:00 貌似犯了重定义的错误，现在在vga_control里写了hit_flag，间接判断是否碰撞
//6.26 16:08 初步测试成功，但撞了一次以后蛇即使按了reset蛇也不能再动，猜测是因为hit_flag没有置0，现在vga_control里加入置0
//6.26 16:58 把hit_flag改成了hit_flag_1和hit_flag_2以判断是谁先撞上谁，开始测试

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
	
	//------------------------控制蛇的速度
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
    
    wire [40:0] speed;//-----------------------------------------------蛇的速度
    
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
