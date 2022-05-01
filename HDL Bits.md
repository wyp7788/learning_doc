# Getting Stared

# Verilog Language

# Circuit

## Combinational Logic

## Sequential Logic

## Building Larger Circuits

- **Counter with period 1000**

Build a counter that counts from 0 to 999, inclusive, with a period of 1000 cycles. The reset input is synchronous, and should reset the counter to 0.

```verilog
module top_module (
    input clk,
    input reset,
    output [9:0] q);
    always @(posedge clk )begin
        if(reset)
            q<=0;
        else 
            q<=(q==999)?0:(q+1);	
    end

endmodule
```

