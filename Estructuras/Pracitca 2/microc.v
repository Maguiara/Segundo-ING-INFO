// 🅿️🚌 Aparcamiento de cursores 🚌🅿️
// ----------------
// |              |
// |              |
// |              |
// ----------------

// TODO:
// - La línea 18, hay que instanciar bien, falta un parámetro

module microc(output wire [5:0] Opcode, output wire z, input wire clk, reset, s_inc, s_inm, we3, wez, input wire [2:0] Op);
//Microcontrolador sin memoria de datos de un solo ciclo
wire [9:0] new_pc, actual_pc, sum_out, mux_1_out;
wire [15:0] instruction;
wire [7:0] RD1, RD2, S, mux_2_out;
wire flag_zero;

// asiggn new_pc = mux_1_out;
// assign Opcode = instruction[15:10];

registro #(10) PC(actual_pc, clk, reset, new_pc);
memprog mem_prog(instruction[15:0], clk, actual_pc);
sum adder(sum_out, actual_pc, 10'b0000000001);
mux2 #(10) mux_1(mux_1_out, sum_out, instruction[9:0], s_inc);
regfile register_bank(RD1, RD2, clk, we3, instruction[3:0], instruction[7:4], instruction[11:8], mux_2_out);
alu ALU(S, flag_zero, RD1, RD2, Op);
mux2 #(8) mux_2(mux_2_out, S, instruction[11:4], s_inm);
ffd FFZ(clk, reset, flag_zero, wez, z);

endmodule