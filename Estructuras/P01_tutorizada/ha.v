module ha(output wire sum, output wire carry, input wire a, input wire b);

    xor xor1(sum, a, b); 
    and and1(carry, a, b);

endmodule 