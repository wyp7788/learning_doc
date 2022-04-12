# NEMU RTFSC

`nemu/include/isa.h`提供ISA相关API的声明

NEMU中的配置系统位于`nemu/tools/kconfig`

在NEMU项目中, "配置描述文件"的文件名都为`Kconfig`, 如`nemu/Kconfig`. 

- `nemu/include/generated/autoconf.h`, 阅读C代码时使用
- `nemu/include/config/auto.conf`, 阅读Makefile时使用



1. 客户程序读入到客户计算机中, 这件事是monitor来负责的. 于是NEMU在开始运行的时候, 首先会调用`init_monitor()`函数(在`nemu/src/monitor/monitor.c`中定义) 来进行一些和monitor相关的初始化工作.



```c
#define STRLEN(CONST_STR) (sizeof(CONST_STR) - 1) //对字符串常量进行计数

#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0])) ////计算数组的长度
//宏连接
#define concat_temp(x, y) x ## y
#define concat(x, y) concat_temp(x, y)
#define concat3(x, y, z) concat(concat(x, y), z)
#define concat4(x, y, z, w) concat3(concat(x, y), z, w)
#define concat5(x, y, z, v, w) concat4(concat(x, y), z, v, w)


```

2. init_isa()(在`nemu/src/isa/$ISA/init.c`中定义), 来进行一些ISA相关的初始化工作.

​	第一项工作就是将一个内置的客户程序读入到内存中

​	内置客户程序放在`nemu/src/isa/$ISA/init.c`

3. NEMU默认为客户计算机提供128MB的物理内存

```c
pmem = malloc(CONFIG_MSIZE);  //CONFIG_MSIZE = 0x8000000 = 2^27Byte 128MB
```

4. `init_isa()`的第二项任务是初始化寄存器, 这是通过`restart()`函数来实现的

5. ```c
   static void restart() {
   
     /* Set the initial program counter. */
   
     cpu.pc = RESET_VECTOR;
   
   
   
     /* The zero register is always 0. */
   
     cpu.gpr[0] = 0;
   
   }
   ```

6. Monitor的初始化工作结束后, `main()`函数会继续调用`engine_start()`函数 (在`nemu/src/engine/interpreter/init.c`中定义). 代码会进入简易调试器(Simple Debugger)的主循环`sdb_mainloop()` (在`nemu/src/monitor/sdb/sdb.c`中定义), 并输出NEMU的命令提示符:

7. 在命令提示符后键入`c`后, NEMU开始进入指令执行的主循环`cpu_exec()` (在`nemu/src/cpu/cpu-exec.c`中定义). `cpu_exec()`又会调用`execute()`, 后者模拟了CPU的工作方式: 不断执行指令. 具体地, 代码将在一个for循环中不断调用`exec_once()`函数, 这个函数的功能就是我们在上一小节中介绍的内容: 让CPU执行当前PC指向的一条指令, 然后更新PC.



## 附录



### ISA相关的API

**全局类型**

```c
word_t; // 表示与ISA字长等长的无符号类型，RISC-V 64-bit 的ISA中为uint64_t
sword_t; //表示与ISA字长等长的有符号类型，RISC-V 64-bit 的ISA中为int64_t
char *FMT_WORD; //word_t对应的十六进制格式化说明符，32-bit ISA 为 "0x%08x". 64-bit ISA 中为 "0x%016lx"
```

**Monitor相关**

```c
char isa_logo; //用于在未实现指令的报错信息中提示开发者阅读相关的文档手册
word_t RESET_VECTOR; //表示PC寄存器初始值
void init_isa(); //在monitor初始化时调用，进行ISA相关的初始化工作；设置必要的寄存器初始值，如PC；加载内置客户程序
```

**寄存器相关**

```c
struct{
    // ...
    
    word_t pc;
    
}CPU_state; //寄存器结构的类型定义，其中必须包含一个PC成员

CPU_state cpu; //寄存器结构的全局定义

void isa_reg_display(); //用于打印寄存器当前的值

word_t isa_reg_str2val(const char *name, bool *success); //若存在名称为name的寄存器，返回其当前值，并设置success为true，否则success为false
```

**执行命令相关**

```c
struct { //用于存放ISA相关的译码信息，会嵌入在译码信息结构体Decode中
    // ... 
}ISADecodeInfo;

int isa_exec_once(Decode *s);//取出 s->pc 指向的指令并译码执行，同时更新 s-> snpc
```

**虚拟内存相关**

```c
int isa_mmu_check(vaddr_t vaddr, int len, int type);
```

检查当前系统状态下对内存区间`[vaddr, vaddr + len]`, 类型为`type`的访问是否需要经过地址转换。其中`type`的类型可能为：

- `MEM_TYPE_LIETCH`：取指令
- `MEM_TYPE_READ`：读数据
- `MEM_TYPE_WRITE`：写数据

函数的返回值可能为：

- `MMU_DIRECT`：该内存访问可以在物理内存上直接进行
- `MMU_TEANSLATE`：该内存访问需要经过机制转换
- `MMU_FAIL`：该内存访问失败，需要抛出异常（如RISC架构不支持非对齐的内存访问）

```C
paddr_t isa_mmu_translate(vaddr_t vaddr, int len, int type);
```

对内存区间为`[vaddr, vaddr + len ]`, 类型为`type`的内存访问进行地址转换，函数返回值可能为：

- `pg_paddr` | `MEM_RET_OK`: 地址转换成功, 其中`pg_paddr`为物理页面的地址(而不是`vaddr`翻译后的物理地址)
- `MEM_RET_FAIL`: 地址转换失败, 原因包括权限检查失败等不可恢复的原因, 一般需要抛出异常
- `MEM_RET_CROSS_PAGE`: 地址转换失败, 原因为访存请求跨越了页面的边界

**中断异常相关**

```c
vaddr_t isa_raise_intr(word_t NO, vaddr_t epc);
```

抛出一个号码为`NO`的异常, 其中`epc`为触发异常的指令PC, 返回异常处理的出口地址.

------

```c
word_t isa_query_intr();
```

查询当前是否有未处理的中断, 若有则返回中断号码, 否则返回`INTR_EMPTY`.

**DiffTest相关**

```c
bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc);
```

检查当前的寄存器状态是否与`ref_r` 相同，`pc`为`cpu.pc`的上一条动态指令的PC，即`cpu.pc`的旧值. 如果状态相同，则返回`true`，否则返回`false` .

```c
void isa_difftest_attach(); 
```

将当前所有状态同步到REF，并在之后的执行中开启`DiffTest`.
