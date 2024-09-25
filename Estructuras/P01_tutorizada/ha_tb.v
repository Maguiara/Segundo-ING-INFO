`timescale 1 ns /  10 ps

module ha_tb;

    wire test_sum, test_carry;
    reg test_a, test_b;
//Hay que poner el mismo nombre que hay dentro del fichero, no el nombre del fichero
    ha ha1(test_sum, test_carry, test_a, test_b);

    //Señales para testear el comportamiento del módulo
    initial 
    begin
        test_a = 1'b0;
        test_b = 1'b0;
        #20;
        test_a = 1'b0;
        test_b = 1'b1;
        #20;
        test_a = 1'b1;
        test_b = 1'b0;
        #20;
        test_a = 1'b1;
        test_b = 1'b1;
        #20;
       $finish;
    end

    //Elementos para poder visualizar el resultado
    initial
    begin 

        $monitor("tiempo=%0d, a=%b, b=%b, suma=%b, acarreo=%b", $time, test_a, test_b, test_sum, test_carry);
        $dumpfile("ha_tb.vcd");
        $dumpvars;

    end

endmodule