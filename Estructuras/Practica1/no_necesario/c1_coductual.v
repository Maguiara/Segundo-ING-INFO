module cl(output reg out, input wire a, input wire b, input wire [1:0] S); //Con reg out conductual

    always @(a,b,S) 
    begin
        case (S)
            2'b00: out = a & b;  // AND
            2'b01: out = a | b;  // OR
            2'b10: out = a ^ b;  // XOR
            2'b11: out = ~a;     // NOT a
            default: out = 1'b0; // Valor por defecto
        endcase
    end

endmodule
