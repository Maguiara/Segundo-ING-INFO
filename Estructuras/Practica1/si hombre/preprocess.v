module preprocess(output wire [3:0] AMod, output wire [3:0] BMod, input wire [3:0] A, input wire [3:0] B, input wire [2:0] Op);



wire add1, op1_A, op2_B, cpl;
wire [3:0] aux1, aux2;
assign add1 = (Op[0]);
assign op1_A = ((Op[1] & ~Op[0]) | (Op[2]));
assign op2_B = ((Op[1] & ~Op[0]) | (Op[2]));
assign cpl = (~Op[2] & ~Op[1] & Op[0]);

mux2_4 mux1(aux1, 4'b0000, 4'b0001 , add1);
mux2_4 mux2(AMod, aux1, A, op1_A);
mux2_4 mux3(aux2, A, B, op2_B);
compl1 compl1(BMod, aux2, cpl);

endmodule