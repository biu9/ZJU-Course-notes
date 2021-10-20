module Out(A_out,OutE,Out);
        input   [7:0]A_out;
        input   OutE;
        output  reg [7:0]Out;
        
        always @(*)begin
                if(OutE) Out = A_out;
        end
endmodule