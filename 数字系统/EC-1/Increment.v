module Increment(Increment_in,Increment_out);
        input   [3:0]Increment_in;
        output  reg [3:0]Increment_out;
        
        always @(*)begin
            Increment_out = Increment_in+1;
        end
endmodule