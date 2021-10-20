module mux2_2(Input,A_in,INmux,mux2_2_out);
        input   [7:0]Input;
        input   [7:0]A_in;
        input   INmux;
        output  reg [7:0]mux2_2_out;
        
        always @(*)begin
                if(INmux) mux2_2_out = Input;
                else mux2_2_out = A_in;
        end
endmodule