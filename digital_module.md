# Digital Design: Basic module

## 1. mux2 to1 构建数字电路

在ECO（Engineering Change Order）阶段，需要使用替补元件（额外的元件）对电路进行修正，使用多路复用器较为方便；使用多路复用器可以构成常见的门电路。

### 1.1 MUX转换为与门

### 1.2 MUX转换为或门

### 1.3 MUX转换为非门

### 1.4 MUX转换为异或门



## 2. 锁存器 Latch

- Latch is transparent high or low

```verilog
module latch(
	input clk,
	input d,
	output reg q
);
    always @(clk or d) begin
       q <= d; 
    end
endmodule
```



- Flip-flop is edge-triggered

```verilog
module flip_flop(
	input clk,
    input d,
    output reg q
);
    always @(posedge clk) begin
    	q <= d;
    end
endmodule
```





## 3. 边沿检测

芯片设计中经常需要进行边沿检测（事件检测），当信号发生变化时，数字系统需要检测这种变化，以此触发相应的电路操作，当输入信号来自不同的时钟域时，需要先进行同步到当前时钟域。

**note：虚线向上的箭头表示时钟上升沿**



### 3.1 同步上升沿检测



<img src="/home/ypwang/learning_doc/image/Screenshot from 2022-04-19 22-08-34.png" alt="Screenshot from 2022-04-19 22-08-34" style="zoom:33%;" /> <img src="/home/ypwang/learning_doc/image/Screenshot from 2022-04-19 22-08-27.png" alt="Screenshot from 2022-04-19 22-08-27" style="zoom: 33%;" /> 

**同步上升边沿检测的电路为一个触发器和与门构成，RTL实现为：**

```verilog
input sig_a;
reg sig_a_d1;
wire sig_a_risedge;

always @(posedge clk or negedge rstb) begin 
    if(!rstb) sig_a_d1 <= 1'b0;
    else      sig_a_d1 <= sig_a;
end

assign sig_a_risedge = sig_a & (!sig_a_d1);
```



### 3.2 同步下升沿检测

<img src="/home/ypwang/learning_doc/image/Screenshot from 2022-04-19 22-16-32.png" alt="Screenshot from 2022-04-19 22-16-32" style="zoom:33%;" /><img src="/home/ypwang/learning_doc/image/Screenshot from 2022-04-19 22-16-44.png" alt="Screenshot from 2022-04-19 22-16-44" style="zoom: 33%;" />

**同步上升边沿检测的电路为一个触发器和与门构成，RTL实现为：**

```verilog
input sig_a;
reg   sig_a_d1;
wire  sig_a_faledge;

always @(posedge clk or negedge rstb) begin
        if(!rstb) sig_a_d1 <= 1'b0;
    	else      sig_a_d1 <= sig_a;
end

assign sig_a_risedge = !sig_a & sig_a_d1;
```



### 3.3 同步上升/下升沿检测

<img src="/home/ypwang/learning_doc/image/Screenshot from 2022-04-19 22-23-03.png" alt="Screenshot from 2022-04-19 22-23-03" style="zoom:33%;" /><img src="/home/ypwang/learning_doc/image/Screenshot from 2022-04-19 22-23-10.png" alt="Screenshot from 2022-04-19 22-23-10" style="zoom:33%;" /> 

**同步上升边沿检测的电路为一个触发器和与门构成，RTL实现为： **

```verilog
input sig_a;
reg   sig_a_d1;
wire  sig_a_anyedge;

always @(posedge clk or negedge rstb) begin
        if(!rstb) sig_a_d1 <= 1'b0;
    	else      sig_a_d1 <= sig_a;
end

assign sig_a_anyedge = sig_a ^ sig_a_d1;
// or 
// assign sig_a_anyedge = (!sig_a & sig_a_d1) | (sig_a & !sig_a_d1);
```



### 3.4 异步输入上升沿检测

![Screenshot from 2022-04-19 22-31-02](/home/ypwang/learning_doc/image/Screenshot from 2022-04-19 22-31-02.png)

![Screenshot from 2022-04-19 22-32-00](/home/ypwang/learning_doc/image/Screenshot from 2022-04-19 22-32-00.png)

由上图可知，前两个触发器的作用为同步数据到同一时钟下，第三个触发器和同步上升沿检测有相同的结构。

**异步上升边沿检测RTL实现为：**

```verilog
module edge_detction(
    input sig_a,
    input clkb,
    input rstb
    );

    reg sig_a_d1, sig_a_d2, sig_a_d3;
    wire sig_a_posedge;

    assign sig_a_posedge = sig_a_d2 & !sig_a_d3;

    always @(posedge clkb or negedge rstb) begin
        if(!rstb) begin
            sig_a_d1 <= 1'b0;
            sig_a_d2 <= 1'b0;
            sig_a_d3 <= 1'b0;
        end
        else begin
            sig_a_d1 <= sig_a;
            sig_a_d2 <= sig_a_d1;
            sig_a_d3 <= sig_a_d2;
        end
        
    end
    
endmodule
```



## 4. 线性反馈移位寄存器（LFSR）

LFSR 用于产生可重复的伪随机序列PRBS，该电路由 n 级触发器和一些异或门组成；在每个时钟周期内，新的输入会被反馈到LFSR内部各个触发器的输入端，输入中的一部分来自于LFSR的输出端，另一部分由LFSR各个输出端进行异或得到。

LFSR的初始值被称为伪随机序列的种子，其最后一个触发器的输出就是一个周期性重复的伪随机序列。



## 5. Gray Code



### 5.1 Gray code to binary code

```verilog
module gray_to_binary #(
    parameter PTR = 8
) (
    gray_value,
    binary_value
);
//***************************
input   [PTR:0] gray_value;
output  [PTR:0] binary_value;
//***************************
wire    [PTR:0] binary_value;

assign binary_value[PTR] = gray_value[PTR];

generate
    genvar i;
    for(i=1;i<(PTR);i=i+1)
    begin
        assign binary_value[i] = gray_value[i+1] ^ gray_value[i];
    end
endgenerate

endmodule
```



### 5.2 Binary code to gray code

```verilog
module binary_to_gray #(
    parameter PTR = 8
) (
    binary_value,
    gray_value
);
//**********************************
input   [PTR:0] binary_value;
output  [PTR:0] gray_value;
//**********************************
wire [PTR:0]gray_value;
generate
    genvar i;
    for(i = 0;i < (PTR);i = i+1)
    begin
        assign gray_value[i] = binary_value[i] ^ binary_value[i+1];
    end
endgenerate

assign gray_value[PTR] = binary_value[PTR];
    
endmodule
```

