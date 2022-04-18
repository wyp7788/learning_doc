# FPGA lab 1：熟悉硬件平台和开发环境

# FPGA Lab 2: 加法器设计

## A Structural and Behavioral Adder Design

### Build a Structural 14-bit Adder

**Method：** Full adder design: structrual design:



```verilog
module full_adder (
    input a,
    input b,
    input carry_in,
    output sum,
    output carry_out
);
    //declearation 
    wire xor_a_b;
    wire cin_and;
    wire and_a_b; 
    // Insert your RTL here to calculate the sum and carry out bits
    
    xor(xor_a_b, a, b);
    and(cin_and, carry_in, xor_a_b);
    and(and_a_b, a, b);

    or(carry_out, and_a_b, cin_and);
    xor(sum, a, b, carry_in);    //to compute sum, the first output
    // Remove these assign statements once you write your own RTL
endmodule
```

**14 bit 行波加法器的构建**

```verilog
`include "full_adder.v"

module structural_adder (
    input [13:0] a,
    input [13:0] b,
    output [14:0] sum
);
    parameter N = 14;
    wire [13:0] co;
    genvar i;
    generate
        for(i = 0; i < N; i = i + 1) begin:bit
            full_adder add(.a(a[i]), .b(b[i]), .carry_in(co[i]), .sum(sum[i]), .carry_out(co[i+1]) );    
        end
    endgenerate
    assign co[0] = 1'b0;
    assign sum[N] = co[N];

    assign sum = a + b;
endmodule
```

# FPGA lab 3：

# FPGA Lab 4: 

# FPGA lab 5：

# FPGA Lab 6:
