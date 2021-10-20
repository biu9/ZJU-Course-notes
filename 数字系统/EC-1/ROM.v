module ROM(adress,ROM_out);
        input   [3:0]adress;
        output  reg [7:0]ROM_out;
        
        always @(*)
        case(adress)
            0:  ROM_out = 8'b01100000;//Input
            1:  ROM_out = 8'b10000000;//Output
            2:  ROM_out = 8'b10100000;//Dec
            3:  ROM_out = 8'b11000001;//JNZ 0001
            4:  ROM_out = 8'b11111111;//Halt
        endcase
endmodule