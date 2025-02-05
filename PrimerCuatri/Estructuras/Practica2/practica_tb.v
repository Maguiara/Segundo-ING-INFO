`timescale 1 ns/ 10 ps

module practica_tb;

//declaracion de las variables necesiarias 
reg clk, reset, s_inc, s_inm, we3, wez, s_skip
reg [2:0] Op;
wire [5:0] Opcode;
wire z; 


//En este caso tendriamos que cambiar el microcontrolador para que acepte tambien s_skip
// y meterle la funcionalidad correspondiente
microc microcontrolador(Opcode, z, clk, reset, s_inc, s_inm, s_skip, we3, wez, Op);

//Generamos un reloj
always begin
  clk = 1'b1;
  #10;
  clk = 1'b0;
  #10;
end

//Señal de reseteo
initial begin
reset = 1'b1;
s_inc = 1'b0;
s_inm = 1'b0;
s_skip = 1'b0;
we3 = 1'b0;
wez = 1'b0;
Op = 3'b000;
end 

//Simulacion por ciclo
initial begin

#10; // Esperamos a que termine el reset
// Ciclo 1: jmp Start
s_inc = 0 //Toma la direcion del salto
s_inm = 0 // No se necesita cargar ningun dato
s_skip = 0 // No hay incremento de 1 o de 2
we3 = 0 // No hay que guardar nada en el register_bank
wez = 0 //Los saltos incondicionales no activan el flag zero
Op = 000 //La ALU no tiene nada que ver en los saltos incondicionales

#20;

// Ciclo 2: li 10 R2
s_inc = 1 // Si no es salto se hace para tener Pc + s_skip
s_inm = 1 // Para los 'li' se pone 1
s_skip = 0 // No hay skip por lo que se incrementa 1
we3 = 1 // Hay dato que guardar en el banco de registros
wez = 0 // 'Li' no actualiza en flag zero
Op = 000 //La ALU no tiene nada que ver cargar datos

#20;

// Ciclo 3: li 4, R1
s_inc = 1 // Si no es salto se hace para tener Pc + s_skip
s_inm = 1 // Para los 'li' se pone 1
s_skip = 0 // No hay skip por lo tanto se incrementa 1
we3 = 1 // Hay dato que guardar en el banco de registros
wez = 0 // 'Li' no actualiza en flag zero
Op = 000 //La ALU no tiene nada que ver cargar datos

#20;

// Ciclo 4: li 7, R3
s_inc = 1 // Si no es salto se hace para tener Pc + s_skip
s_inm = 1 // Para los 'li' se pone 1
s_skip = 0 // No hay skip por lo tanto se incrementa 1
we3 = 1 // Hay dato que guardar en el banco de registros
wez = 0 // 'Li' no actualiza en flag zero
Op = 000 //La ALU no tiene nada que ver cargar datos

#20;

// Ciclo 5: li 7, R3
s_inc = 1 // Si no es salto se hace para tener Pc + s_skip
s_inm = 1 // Para los 'li' se pone 1
s_skip = 0 // No hay skip por lo tanto se incrementa 1
we3 = 1 // Hay dato que guardar en el banco de registros
wez = 0 // 'Li' no actualiza en flag zero
Op = 000 //La ALU no tiene nada que ver cargar datos

#20;

// Ciclo 6: li 1, R4
s_inc = 1 // Si no es salto se hace para tener Pc + s_skip
s_inm = 1 // Para los 'li' se pone 1
s_skip = 0 // No hay skip por lo tanto se incrementa 1
we3 = 1 // Hay dato que guardar en el banco de registros
wez = 0 // 'Li' no actualiza en flag zero
Op = 000 //La ALU no tiene nada que ver cargar datos

#20;


// Ciclo 7: add R2, R3, R2
s_inc = 1 // Si no es salto se hace para tener Pc + s_skip
s_inm = 0 // No se necesita cargar ningun dato
s_skip = 0 // No hay skip por lo tanto se incrementa 1
we3 = 1 // Hay dato que guardar en el banco de registros
wez = 1 // Se actualiza el flag de 0
Op = 010 // Operacion de suma

#20;

// Ciclo 8: sub R1, R4, R1
s_inc = 1 // Si no es salto se hace para tener Pc + s_skip
s_inm = 0 // No se necesita cargar ningun dato
s_skip = 0 // No hay skip por lo tanto se incrementa 1
we3 = 1 // Hay dato que guardar en el banco de registros
wez = 1 // Se actualiza el flag de 0
Op = 011 // Operacion de resta

#20;

// Ciclo 9: skipep R1, R4 
s_inc = 1 // Si no es salto se hace para tener Pc + s_skip
s_inm = 0 // No se necesita cargar ningun dato
s_skip = 1 // Se activa la señal para ver si se salta 1 o 2
we3 = 1 // Hay dato que guardar en el banco de registros
wez = 1 // Se actualiza el flag de 0
Op = 011 // Operacion de resta

#20;

// Ciclo 10: jmp Iter 
s_inc = 0 // Se pone 0 para que PC coja la dirreccion del salto
s_inm = 0 // No se necesita cargar ningun dato
s_skip = 0 // No se activa la señal
we3 = 0 // Hay dato que guardar en el banco de registros
wez = 0 // Los saltos incondicionales no actualizan el flag zero
Op = 000 // La ALU no tiene nada que ver en los saltos

#20;

// Ahora hay que hacerlos tantas veces como iteracioens haya
// Indicar en el ultimo ciclo que hay un bucle infinito 

end 

  
endmodule