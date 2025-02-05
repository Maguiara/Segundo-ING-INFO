module sum4(output wire[3:0] S, output wire c_out, input wire[3:0] A, input wire[3:0] B, input wire c_in);


  //wire c1, c2, c3;
  wire [3:1] c;
  fa fa1(c[1], S[0], A[0], B[0], c_in); 
  fa fa2(c[2], S[1], A[1], B[1], c[1]);
  fa fa3(c[3], S[2], A[2], B[2], c[2]);
  fa fa4(c_out, S[3], A[3], B[3], c[3]);

endmodule