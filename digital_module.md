# Digital module

## 1. 边沿检测

芯片设计中经常需要进行边沿检测（事件检测），当信号发生变化时，数字系统需要检测这种变化，以此触发相应的电路操作，当输入信号来自不同的时钟域时，需要先进行同步到当前时钟域。

**note：虚线向上的箭头表示时钟上升沿**



### 1.1 同步上升沿检测



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



### 1.2 同步下升沿检测

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



### 1.3 同步上升/下升沿检测

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



### 1.4 异步输入上升沿检测

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



## 2. 线性反馈移位寄存器（LFSR）

LFSR 用于产生可重复的伪随机序列PRBS，该电路由 n 级触发器和一些异或门组成；在每个时钟周期内，新的输入会被反馈到LFSR内部各个触发器的输入端，输入中的一部分来自于LFSR的输出端，另一部分由LFSR各个输出端进行异或得到。

LFSR的初始值被称为伪随机序列的种子，其最后一个触发器的输出就是一个周期性重复的伪随机序列。