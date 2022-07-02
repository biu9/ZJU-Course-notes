## lab 3.1
### overview
The learning objective of this lab is for students to gain the first-hand experience on using static code analysis tools to check c program for security vulnerabilities and coding mistakes.

your goal is to achieve the followings:
- Install splint;
- Finish code samples with 2 different kinds of problems which can be detected by Splint. You can choose any 2 of 11 problems as above.
- Use splint to detect the 2 kinds of problems. Descibe your observations in your report.
### install splint
![20220602102419](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/20220602102419.png)
![20220602102438](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/20220602102438.png)


### Finish code samples with 2 different kinds of problems
#### Problem code 1
使用如下代码进行漏洞分析
```C
#include<stdio.h>
#include<string.h>

int main() {
	char test[100];
	scanf("%s", test);
	printf(test);
	return 1;
}
```
#### Problem code 2
使用如下代码进行漏洞分析
```C
#include<stdio.h>

int main() {
    int a = 0;
    int b = 1;
    if(a = b) {
        printf("wrong");
    }
}
```

### Use splint to detect the 2 kinds of problems.
对于test1.c,分析得到如下结果,可以看到,splint检测到了两个错误,一个是程序没有注意scanf函数的返回值,另一个是典型的格式化字符串漏洞
![20220602223630](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/20220602223630.png)

对于test2.c,分析得到如下结果,splint检测到了三个错误,一个是使用了if(a = b),一个是if()内的表达式既不是Boolean也不是int,还有一个是main函数没有写返回值
![20220602223708](https://typora-1309407228.cos.ap-shanghai.myqcloud.com/20220602223708.png)
