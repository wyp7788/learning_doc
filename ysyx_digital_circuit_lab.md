# YSYX 预学习数字电路基础实验

## 1. Lab_1 选择器

### 1.1 2选1多路选择器

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







## 2. Lab_2 译码器和编码器

## 3. Lab_3 加法器和ALU

