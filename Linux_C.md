# Linux C编程





## 1. C 语言基础

C语言的设计理念：自顶向下、结构化和模块化设计

程序告诉计算机应该如何完成一个计算任务，程序由一系列指令（Instruction）组成。

**key** **point**:

```c
#define assert(cond) if(!(cond)) pandic();
```

assert()  是一个宏，不是一个函数，如果出现：

```c
if (...) assert(0);   
else ...
    
//上面代码编译器翻译为
if(...)
    if(!0) panic();
else ...                 //由于else与最近的if配对，所以会出现错误
    
/*
*下面是正确的写法
*/
#define assert(cond) \
  do { \
    if (!(cond)) { \
      fprintf(stderr, "Fail @ %s:%d", __FILE__, __LINE__); \
      exit(1); \
    } \
  } while (0)

#define assert(cond) ({ ... })
```



assert**主要用于类型检查及单元测试中**





## 2. C语言深入理解

## 3. Linux C编程

## 附录 

### 1. Makefile 

**make** 命令执行时，需要Makefile文件，Makefile文件规定了make命令如何编译和链接程序。

**make** 命令会自动读取当前目录下的Makefile文件，完成相应的编译步骤。Makefile由一组规则组成，每条**Makefile 规则**格式为：

```makefile
target :prerequisites ...
		command1
		command2
		...
```

**target （目标）：**目标文件，也可以是执行文件，还可以是一个标签；

**prerequisites ：**生成target所需要的文件（条件）

**command：** make需要执行的命令（任意的shell命令）

欲更新目标，必须首先更新它的所有条件，所有条件中只要有一个条件被更新，目标也随之被更新。**更新就是执行一遍规则中的命令列表，命令列表中的每条命令必须用Tab开头，且不能有空格。**

例如：

```makefile
main: main.o stack.o maze.o
	gcc main.o stack.o maze.o
```

//例子讲解

### 2. Linux常用命令

```shell
find  . # 查看当前目录下面所有文件
tree . # 查看当前目录文件树
find . -name "*.c"  # 查看当前目录下所有 .c文件
find . -name "*.c" -o -name "*.h" # 查看当前目录下.c 或者是.h文件 -o: or
find . -name "*.c" -o -name "*.h" | xargs cat   # 管道，将find的结果送入管道作为xargs 的输入
-wc  # word count 
vim . # 在终端打开当前目录下所有文件
lscpu # 查看cpu信息
```

#### 2.1 vim 操作

![](/home/ypwang/learning_doc/image/Screenshot from 2022-03-14 08-38-33.png)
```shell

```

#### 2.2 进程

### 3. Git Tutorial for me
#### 3.1 Git 常用命令

