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

多路选择器模板：



```verilog
module MuxKeyInternal #(NR_KEY = 2, KEY_LEN = 1, DATA_LEN = 1, HAS_DEFAULT = 0) (
  output reg [DATA_LEN-1:0] out,
  input [KEY_LEN-1:0] key,
  input [DATA_LEN-1:0] default_out,
  input [NR_KEY*(KEY_LEN + DATA_LEN)-1:0] lut
);

  localparam PAIR_LEN = KEY_LEN + DATA_LEN;
  wire [PAIR_LEN-1:0] pair_list [NR_KEY-1:0];
  wire [KEY_LEN-1:0] key_list [NR_KEY-1:0];
  wire [DATA_LEN-1:0] data_list [NR_KEY-1:0];

  generate
    for (genvar n = 0; n < NR_KEY; n = n + 1) begin
      assign pair_list[n] = lut[PAIR_LEN*(n+1)-1 : PAIR_LEN*n];
      assign data_list[n] = pair_list[n][DATA_LEN-1:0];
      assign key_list[n]  = pair_list[n][PAIR_LEN-1:DATA_LEN];
    end
  endgenerate

  reg [DATA_LEN-1 : 0] lut_out;
  reg hit;
  integer i;
  always @(*) begin
    lut_out = 0;
    hit = 0;
    for (i = 0; i < NR_KEY; i = i + 1) begin
      lut_out = lut_out | ({DATA_LEN{key == key_list[i]}} & data_list[i]);
      hit = hit | (key == key_list[i]);
    end
    if (!HAS_DEFAULT) out = lut_out;
    else out = (hit ? lut_out : default_out);
  end

endmodule

/*
* MuxKey 模块实现了“键值选择”功能，即在一个 `(键值，数据)` 的列表 `lut` 中
* 根据给定的键值 key ，将 out 设置为与其匹配的数据
*/

module MuxKey #(NR_KEY = 2, KEY_LEN = 1, DATA_LEN = 1) (
  output [DATA_LEN-1:0] out,
  input [KEY_LEN-1:0] key,
  input [NR_KEY*(KEY_LEN + DATA_LEN)-1:0] lut
);
  MuxKeyInternal #(NR_KEY, KEY_LEN, DATA_LEN, 0) i0 (out, key, {DATA_LEN{1'b0}}, lut);
endmodule


/* 
* 提供一个默认值default_out
* 若列表中不存在键值为key的数据，则输出为0
*/
module MuxKeyWithDefault #(NR_KEY = 2, KEY_LEN = 1, DATA_LEN = 1) (   
  output [DATA_LEN-1:0] out,
  input [KEY_LEN-1:0] key,
  input [DATA_LEN-1:0] default_out,
  input [NR_KEY*(KEY_LEN + DATA_LEN)-1:0] lut
);
  MuxKeyInternal #(NR_KEY, KEY_LEN, DATA_LEN, 1) i0 (out, key, default_out, lut);
endmodule
```



`MuxKey` 模块实现了“键值选择”功能，即在一个 `(键值，数据)` 的列表 `lut` 中，根据给定的键值 `key` ，将 `out` 设置为与其匹配的数据。若列表中不存在键值为 `key` 的数据，则 `out` 为 `0` 。特别地， `MuxKeyWithDefault` 模块可以提供一个默认值 `default_out` ，当列表中不存在键值为 `key` 的数据，则 `out` 为 `default_out`







#### Lab2 译码器和编码器

**功能描述**

查找8-3优先编码器相关原理和实现方法，实现一个8-3编码器，完成8-3编码器的设计、功能仿真和硬件实现。

输入一个8位二进制数，对此8位二进制数进行高位优先编码成一个3位二进制值，并根据是否有输入增加一位输入指示位，即8个输入全0时指示位为0，有任何一个输入为1时指示位为1。编码器的使能端可选实现。将此编码结果及指示位以二进制形式显示在四个发光二极管LED上。再将此结果跟据七段数码管的显示进行译码，将二进制的优先编码结果以十进制的形式显示在数码管上。

**输入输出建议**

输入可以使用拨动开关SW7-SW0。使能端可以用SW8。输出为LED2-0，输出指示可以是LED4，数码管输出为HEX0。

例：我们从SW7—SW0输入00001110，因为我们设计的是一个高位优先的优先编码器，从左（高位）开始，第一位为1的是第3号位，那么优先编码器的编码二进制结果就为011，将这个值显示在发光二极管上，并且指示位也同时置为1。再对这个数值跟据七段数码管的显示进行译码，此时应显示为 `3` ，用HEX0显示，所以HEX0[6:0]应该译码为0110000（注意高低位顺序），那么在七段数码管上就会显示 `3` 这个字符。













#### Lab 3 加法器与ALU



#### Lab 4 计数器和时钟（zynq 7020 实现）

```verilog
module timertick_gen(
    //CLK_125MHZ_FPGA,        // sw resetb;
    input CLK_125MHZ_FPGA,
    input  SWITCHES,
     
    output reg us_tick,
    output reg ms_tick,
    output reg sec_tick,
    output reg  [9:0]   sec_counter
    //output [9:0]LEDS
);
//**************************




parameter US_COUNTER_MAX = 8'd124;       // 125M Hz  

wire resetb;

reg  [7:0]   us_counter;
wire [7:0]   us_counter_nxt;
//reg          us_tick;
wire         us_tick_nxt;

reg  [9:0]   ms_counter;
reg  [9:0]   ms_counter_nxt;
//reg          ms_tick;
wire         ms_tick_nxt;

//reg  [9:0]   sec_counter;
wire [9:0]   sec_counter_nxt;
//reg          sec_tick;
wire         sec_tick_nxt;
//******************************************
assign us_counter_nxt = (us_counter == US_COUNTER_MAX) ? 'd0 : (us_counter + 1'b1);
assign us_tick_nxt = (us_counter == US_COUNTER_MAX);
//*******************************************
// ms counter
always @(*) begin
    ms_counter_nxt = ms_counter;
    if(us_tick)begin
        if(ms_counter == 'd999)
            ms_counter_nxt = 0;
        else ms_counter_nxt = ms_counter + 1;
    end    
end

assign ms_tick_nxt = (ms_counter == 'd999);

assign sec_counter_nxt = ms_tick  ? ((sec_counter == 'd999) ? 'd0 : (sec_counter + 1'b1)) : sec_counter;

assign sec_tick_nxt = (sec_counter == 'd999);

always @(posedge CLK_125MHZ_FPGA or negedge resetb) begin
    if(!resetb)begin
        us_counter  <= 'd0;
        ms_counter  <= 'd0;
        sec_counter <= 'd0;
        us_tick     <= 1'b0;
        ms_tick     <= 1'b0;
        sec_tick    <= 1'b0;
    end
    else begin
        us_counter <= us_counter_nxt;
        ms_counter <= ms_counter_nxt;
        sec_counter <= sec_counter_nxt;
        us_tick     <= us_tick_nxt;
        ms_tick     <= ms_tick_nxt;
        sec_tick    <= sec_tick_nxt; 
    end
end

assign resetb = SWITCHES;
//assign LEDS = sec_counter;

endmodule
```



#### Lab 5 寄存器组及存储器（zynq 7020 实现）



**寄存器组(RISC-V 64寄存器组)实现verilog：**

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

在RV32I指令集中需要实现32位数据的移位，应该如何用Verilog语言实现？

我们可以利用8位移位寄存器来实现一个简单的随机数发生器。 经典的LFSR（线性反馈移位寄存器， [Linear-feedback shift register](https://en.wikipedia.org/wiki/Linear-feedback_shift_register) ）可以使用n位移位寄存器生成长度为 2n−1 的二进制循环序列。 这类序列的片段在表观上是随机的，所以被广泛用于通信中的随机序列生成。例如，在CDMA通信中的长码的长度就是 242−1 的伪随机序列。

具体实现时，可以用一个8位右移移位寄存器，从左到右的比特以 x7x6x5x4x3x2x1x0 表示。每个时钟周期右移一位， x0 被移出，最左边移入的位按照上一周期的值计算 [1](https://nju-projectn.github.io/dlco-lecture-note/exp/06.html#f1) ：

x8=x4⊕x3⊕x2⊕x0

例如，初始二进制值为00000001时，移位寄存器的状态将按 00000001→10000000→01000000→001000000→00010000→10001000… 变化。 该序列的周期为255。 当然，当初始值为全零时，系统将一直停留在全零状态，所以需要对全零状态进行特殊处理。

请实现一个8位的周期为255的伪随机序列，以按钮为时钟信号，并请将8位二进制数以十六进制显示在数码管上，在DE10-Standard开发板上观察生成的随机数序列。

生成的伪随机数序列仍然有一定的规律，如何能够生成更加复杂的伪随机数序列？

#### Lab 7 状态机及键盘输入

#### Lab 8 VGA接口控制器实现

```verilog
module vga_ctrl(
    input           pclk,     //25MHz时钟
    input           reset,    //置位
    input  [23:0]   vga_data, //上层模块提供的VGA颜色数据
    output [9:0]    h_addr,   //提供给上层模块的当前扫描像素点坐标
    output [9:0]    v_addr,
    output          hsync,    //行同步和列同步信号
    output          vsync,
    output          valid,    //消隐信号
    output [7:0]    vga_r,    //红绿蓝颜色信号
    output [7:0]    vga_g,
    output [7:0]    vga_b
    );

  //640x480分辨率下的VGA参数设置
  parameter    h_frontporch = 96;
  parameter    h_active = 144;
  parameter    h_backporch = 784;
  parameter    h_total = 800;

  parameter    v_frontporch = 2;
  parameter    v_active = 35;
  parameter    v_backporch = 515;
  parameter    v_total = 525;

  //像素计数值
  reg [9:0]    x_cnt;
  reg [9:0]    y_cnt;
  wire         h_valid;
  wire         v_valid;

  always @(posedge reset or posedge pclk) //行像素计数
      if (reset == 1'b1)
        x_cnt <= 1;
      else
      begin
        if (x_cnt == h_total)
            x_cnt <= 1;
        else
            x_cnt <= x_cnt + 10'd1;
      end

  always @(posedge pclk)  //列像素计数
      if (reset == 1'b1)
        y_cnt <= 1;
      else
      begin
        if (y_cnt == v_total & x_cnt == h_total)
            y_cnt <= 1;
        else if (x_cnt == h_total)
            y_cnt <= y_cnt + 10'd1;
      end
  //生成同步信号
  assign hsync = (x_cnt > h_frontporch);
  assign vsync = (y_cnt > v_frontporch);
  //生成消隐信号
  assign h_valid = (x_cnt > h_active) & (x_cnt <= h_backporch);
  assign v_valid = (y_cnt > v_active) & (y_cnt <= v_backporch);
  assign valid = h_valid & v_valid;
  //计算当前有效像素坐标
  assign h_addr = h_valid ? (x_cnt - 10'd145) : {10{1'b0}};
  assign v_addr = v_valid ? (y_cnt - 10'd36) : {10{1'b0}};
  //设置输出的颜色值
  assign vga_r = vga_data[23:16];
  assign vga_g = vga_data[15:8];
  assign vga_b = vga_data[7:0];
endmodule
```



#### Lab 9 字符输入界面

