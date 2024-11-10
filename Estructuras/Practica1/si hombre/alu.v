module alu(output wire [3:0] R, output wire zero, carry, sign, input wire [3:0] A, B, input wire c_in, input wire [2:0] Op);

wire [3:0] AMod_, BMod_, aux1_, aux2_;
preprocess preprocess1(AMod_, BMod_, A, B, Op);
sum4 sum4_1(aux1_, carry, AMod_, BMod_, c_in);
ul4 ul4_1(aux2_, AMod_, BMod_, Op[1:0]);
mux2_4 mux2_41(R, aux1_, aux2_, Op[2]);

assign zero = (R == 4'b0000);
assign sign = R[3];

endmodule