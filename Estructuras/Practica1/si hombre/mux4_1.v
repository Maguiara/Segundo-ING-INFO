module mux4_1(output reg out, input wire a, input wire b, input wire c, input wire d, input wire [1:0] S);

    //Ejemplo de multiplexor de 4 entradas de forma estructural.

    /* wire and_out, or_out, xor_out, neg_out;
        and and1(and_out, a, b);
        or or1(or_out, a, b);
        xor xor1(xor_out, a, b);
        not not1(neg_out, a);
        mux4_1  mux1(out, and_out, or_out, xor_out, neg_out, S);

    */

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
