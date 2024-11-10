module fa(output wire c_out, sum, input wire a, b, c_in);

  // Sin extension de {c_out, sum} = a + b + c_in;
  // assign sum = a ^ b ^ c_in;
  // assign c_out = (a & b) | (b & c_in) | (a & c_in);

  assign {c_out, sum} = a + b + c_in;

endmodule