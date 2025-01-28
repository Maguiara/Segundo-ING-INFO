
module cl(output wire out, input wire a, input wire b, input wire [1:0] S); //Con wire out estructural 

    wire and_out, or_out, xor_out, neg_out;

    and and1(and_out, a, b);
    or or1(or_out, a, b);
    xor xor1(xor_out, a, b);
    not not1(neg_out, a);
    mux4_1  mux1(out, and_out, or_out, xor_out, neg_out, S); 

endmodule
