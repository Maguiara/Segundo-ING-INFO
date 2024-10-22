`timescale 1ns / 1ps

module mux4_tb;

    // Inputs
    reg [1:0] sel;
    reg [3:0] d;

    // Outputs
    wire y;

    // Instantiate the Unit Under Test (UUT)
    mux4 uut (
        .sel(sel), 
        .d(d), 
        .y(y)
    );

    initial begin
        // Initialize Inputs
        sel = 0;
        d = 0;

        // Wait 100 ns for global reset to finish
        #100;
        
        // Test case 1
        sel = 2'b00; d = 4'b0001; #10;
        if (y !== d[0]) $display("Test case 1 failed");

        // Test case 2
        sel = 2'b01; d = 4'b0010; #10;
        if (y !== d[1]) $display("Test case 2 failed");

        // Test case 3
        sel = 2'b10; d = 4'b0100; #10;
        if (y !== d[2]) $display("Test case 3 failed");

        // Test case 4
        sel = 2'b11; d = 4'b1000; #10;
        if (y !== d[3]) $display("Test case 4 failed");

        $display("All test cases passed");
        $finish;
    end
      
endmodule