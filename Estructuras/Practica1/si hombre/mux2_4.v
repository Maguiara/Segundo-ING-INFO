
module mux2_4(output wire [3:0] Out, input wire [3:0] A, input wire [3:0] B, input wire s);

    /**
    // Procedural
    always @(*) begin
        if (s) begin
            Out = B;
        end else begin
            Out = A;
        end
    end
    */

    assign Out = s ? B : A;

endmodule