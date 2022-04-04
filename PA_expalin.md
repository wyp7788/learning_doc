# PA :Programming Assignment

## 环境

- CPU架构: x64
- 操作系统: GNU/Linux
- 编译器: GCC
- 编程语言: C语言











### PA1 RTFSC



make run :

![Screenshot from 2022-04-04 22-38-51](/home/ypwang/learning_doc/image/Screenshot from 2022-04-04 22-38-51.png)

menuconfig 

```shell
make menucofig
```

打开

```shell
Build Options
	[*] Enable debug information
```



![Screenshot from 2022-04-04 22-41-55](/home/ypwang/learning_doc/image/Screenshot from 2022-04-04 22-41-55.png)

make clean之后运行make run

![Screenshot from 2022-04-04 22-43-44](/home/ypwang/learning_doc/image/Screenshot from 2022-04-04 22-43-44.png)



如何优美地退出？

在nemu目录下运行make run之后，会出现：
![Screenshot from 2022-04-04 22-29-20](/home/ypwang/learning_doc/image/Screenshot from 2022-04-04 22-29-20.png)

使用GDB调试，定位错误位置，
