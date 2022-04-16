### 数字电路基础实验



#### Lab1 数据选择器

多路选择器框图为

<img src="/home/ypwang/learning_doc/image/Screenshot from 2022-03-26 00-04-21.png" style="zoom: 50%;" /> 

**真值表为：**

| s    | a    | b    | y    |
| ---- | ---- | ---- | ---- |
| 0    | 0    | 0    | 0    |
| 0    | 0    | 1    | 0    |
| 0    | 1    | 0    | 1    |
| 0    | 1    | 1    | 1    |
| 1    | 0    | 0    | 0    |
| 1    | 0    | 1    | 1    |
| 1    | 1    | 0    | 0    |
| 1    | 1    | 1    | 1    |

```C++
y = s'ab' + s'ab +sa'b + sab;
y = s'a + ab
```

故多路选择题电路为：

<img src="/home/ypwang/learning_doc/image/Screenshot from 2022-03-26 00-04-34.png" alt="Screenshot from 2022-03-26 00-04-34" style="zoom:50%;" />

多路选择器的Verilog描述为：

```verilog
// behavior modeling
module lab1_mux21 (
    input a,
    input b,
    input s,
    output y
);
assign y = (~s & a) | (s & b);
    
endmodule

//structure modeling
module lab1_mux21b(a,b,s,y);
  input  a,b,s;
  output y;

  wire l, r, s_n; 
  my_not i1(.a(s), .b(s_n));    
  my_and i2(.a(s_n), .b(a), .c(l));
  my_and i3(.a(s),   .b(b), .c(r)); 
  my_or  i4(.a(l),   .b(r), .c(y));
endmodule

module my_and(a,b,c);
  input  a,b;
  output c;

  assign c = a & b;
endmodule

module my_or(a,b,c);
  input  a,b;
  output c;

  assign c = a | b;
endmodule

module my_not(a,b);
  input  a;
  output b;

  assign b = ~a;
endmodule
```



#### Lab2 译码器和编码器



#### Lab 3 加法器与ALU



#### Lab 4 计数器和时钟（zynq 7020 实现）

#### Lab 5 寄存器组及存储器（zynq 7020 实现）

**寄存器组(RV64寄存器组)实现verilog：**

```verilog
module rv64im_regs (
	input clk, wen, 	// write enable and clock
	input [4:0] rw,		// write select
	input [4:0] ra,
	input [4:0] rb,
	input [63:0] busw,	//64-bit data bus
	output [63:0] busa,
	output [63:0] busb
);

	reg [63:0] regs [31:0];
	always @(posedge clk)
		if(wen) regs[rw] <= busw;
	assign busa = (ra == 5'd0) ? 64'd0 : regs[ra];
	assign busb = (rb == 5'd0) ? 64'd0 : regs[rb];

endmodule

```



#### Lab 6 移位寄存器及桶形移位器

#### Lab 7 状态机及键盘输入

#### Lab 8 VGA接口控制器实现

#### Lab 9 字符输入界面

