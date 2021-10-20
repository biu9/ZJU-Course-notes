module Derement(PC_in,PC_D_out);
        input   [7:0]PC_in;
        output  reg [7:0]PC_D_out;
        
        always @(*)begin
                PC_D_out = PC_in-1'b1;
        end
endmodule