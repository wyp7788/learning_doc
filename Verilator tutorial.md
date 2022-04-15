# Verilator tutorial

![verilator usage](/home/ypwang/learning_doc/image/verilator_usage_400x200-min.png)

## 1. Verilog  -> C++ file

```shell
verilator -Wall --cc --exe --build sim_main.cpp our.v   
# -Wall 打开所有警告信息
# --cc to get C++ output
# --exe 
# --build 
```

> 两步生成可执行文件：
>
> - `verilator -Wall --cc --exe Vmodule.cpp module.v`
> - `make -j -C obj_dir -f Vour.mk Vour` 

以上两步执行完之后就会生成可执行的仿真文件



# Verilator 仿真过程

> - 1.RTL设计代码
> - 2.Verilog 生成接口文件
> - 3.根据生成的接口文件写testbench
> - testbench 构建生成可执行文件进行仿真

### 1. RTL 设计

以流水灯为例, Verilog代码如下：`light.v` 

```verilog
module light(
  input clk,
  input rst,
  output reg [5:0] led
);
    reg [9:0] count;
  always @(posedge clk) begin
    if (rst) begin 
        led <= 1; 
        count <= 0; 
    end
    else begin
      if (count == 0) 
          led <= {led[4:0], led[5]};
      count <= (count >= 5000000 ? 32'b0 : count + 1);
    end
  end
endmodule
```



### 2. Verilog生成Verilated Model

```shell
verilator --cc light.v
```

运行完上述命令会生成一个`obj_dir`

```shell
ls -l obj_dir/
# 生成的文件
total 44
-rw-rw-r-- 1  Vlight___024root.cpp
-rw-rw-r-- 1  Vlight___024root.h
-rw-rw-r-- 1  Vlight___024root__Slow.cpp
-rw-rw-r-- 1  Vlight_classes.mk
-rw-rw-r-- 1  Vlight.cpp
-rw-rw-r-- 1  Vlight.h
-rw-rw-r-- 1  Vlight.mk
-rw-rw-r-- 1  Vlight__Syms.cpp
-rw-rw-r-- 1  Vlight__Syms.h
-rw-rw-r-- 1  Vlight__ver.d
-rw-rw-r-- 1  Vlight__verFiles.dat
```

- `Vlight.h ` Include model header, generated from Verilating "RTL.v"
- `Vlight.cpp`提供仿真的信号接口；
- `Vlight.mk`与`make`一起使用构建可执行仿真文件；



### 3. Write testbench for your RTL design

Verilator的`testbench`使用C++编写，假设前期的RTL代码为`RTL.v`基本过程为：

（1）头文件包含：

```C++
// Include common routines
#include <verilated.h>   

// Include model header, generated from Verilating "RTL.v"
#include "Vtop.h"
```

（2）主函数



`verilator -Wall --trace -cc alu.sv --exe tb_alu.cpp`













# 附录

```C++
 // Prevent unused variable warnings 
 if (false && argc && argv && env) {}
```







