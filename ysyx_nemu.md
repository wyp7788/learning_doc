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
