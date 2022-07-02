## lab 2.4
### goal
your goal is to achieve the followings (not necessarily at the same time):

- Crash the program named "vul_prog.c".
- Print out the secret[1] value.
- Modify the secret[1] value.
- Modify the secret[1] value to a pre-determined value.
### steps
1. Crash the program named "vul_prog.c".
   
   输入多个%s即可
   ![20220601153731](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/20220601153731.png)
2. Print out the secret[1] value.
   
   通过输入AAAA-%X-%X-%X...我们可以依次打印出栈中的值,我们可以发现,之前输入的user_input在第九个的位置,由此,我们可以通过%9$s读取这个地址处的数据,我们只需要将user_input设置为secret[1]的地址即可
   ![20220601152805](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/20220601152805.png)
3. Modify the secret[1] value.
   
   使用%n可以修改当前地址处的值为输出字符的数字,%x%x%x%x%x%x%x%x%n可以把secret[1]的值修改为0x40
   ![20220601153014](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/20220601153014.png)
4. Modify the secret[1] value to a pre-determined value.
   
   我们可以在%x%x%x%x%x%x%x%x后添加任意长度的输出以控制secret[1]的值,举例而言,在%x%x%x%x%x%x%x%x后添加十六个输出就可以使得secret[1]的值为0x50
   ![20220601153602](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/20220601153602.png)