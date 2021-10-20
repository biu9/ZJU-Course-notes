module mux2_1(IR_in,mux2_1_out,JNZmux,PC_in);
        input   [3:0]IR_in;
        input   JNZmux;
        input   [3:0]PC_in;
        output  reg [3:0]mux2_1_out;
        
        always @(*) begin
                if(JNZmux) mux2_1_out = IR_in;
                else mux2_1_out = PC_in;
        end
endmodule