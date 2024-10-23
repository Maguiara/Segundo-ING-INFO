module mux4_1(output reg out, input wire a, input wire b, input wire c, input wire d, input wire [1:0] S);

    always @(a,b,c,d,S) 
    begin
        //Dependiendo del vector S, el multiplexor escoge una de sus 4 salidas.
        case(S)
            2'b00: out = a;
            2'b01: out = b;
            2'b10: out = c;
            2'b11: out = d;
            default: out = 1'b0; //Valor por defecto
        endcase
    end

endmodule
