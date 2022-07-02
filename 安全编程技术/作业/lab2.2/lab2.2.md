## lab 2.2
### overview
Overview
The lab helps familiarize you with writing a simple Hello World program using C, the GCC compiler link, and Pico(a text editor, link). It uses Ubuntu VM created in Lab 2.1.Here is lab objective:
- Learn to run a program in gcc.
- Learn to debug a program in gdb.
  
### steps
1. 调用gdb，gcc编译并调试`gcc -g debug_me.c -o debug_me`

   ![image-20220522233856519](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220522233856519.png)

2. 在gdb中运行程序

   ````shell
   gdb debug_me
   run "hello, world" "goodbye, world"
   ````

   ![image-20220522234017427](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220522234017427.png)

3. 设置断点
   ![20220606141250](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/20220606141250.png)

4. 运行到第七行后查看frame
   ![image-20220522234342474](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220522234342474.png)

5. next与step的区别
   1. step是单步执行，遇到子函数就进入并且继续单步执行。
   2. next是在单步执行时，在函数内遇到子函数时不会进入子函数内单步执行，而是将子函数整个执行完再停止，也就是把子函数整个作为一步。