# Problem 1

### a.

$$
||x||_∞=max|x_i|\\
||x-\tilde{x}||_∞=max|(x-\tilde x)_i|=0.5\\
A=
[\begin{matrix}
1&2&3\\
2&3&4\\
3&4&6
\end{matrix}]\\
A\tilde{x}-b=(1,-1.3,1.8)^t\\
||A\tilde{x}-b||_∞=1.8
$$

### b.

$$
||x||_∞=max|x_i|\\
||x-\tilde{x}||_∞=max|(x-\tilde x)_i|=0.9\\
A=
[\begin{matrix}
1&2&3\\
2&3&4\\
3&4&6
\end{matrix}]\\
A\tilde{x}-b=(1.27,-1.16,2.21)^t\\
||A\tilde{x}-b||_∞=2.21
$$

# Problem 2

$$
由于||A||_2=[\rho(A^tA)^\frac{1}{2}]\\
若A是对称的，则A^tA=A*A\\
||A||_2=[\rho(A^tA)^\frac{1}{2}]=\rho(A)
$$

# Problem 3

> 本题采用三位精度

### a.

$$
s_1=58.9~~~s_2=6.1\\
\frac{|a_{11}|}{s_1} = 0.000509337\\
\frac{|a_{21}|}{s_2} = 0.870491803\\
\frac{|a_{21}|}{s_2}>\frac{|a_{11}|}{s_1}\\
交换后的矩阵为：\\
[\begin{matrix}
5.31&-6.1&47\\
0.03&58.9&59.2\\
\end{matrix}]\\
一次高斯消元以后得到的矩阵如下：\\
[\begin{matrix}
5.31&-6.1&47\\
-1.5*10^{-6}&58.934&58.934
\end{matrix}]\\
=>\\
[\begin{matrix}
5.31&-6.1&47\\
0&58.934&58.934
\end{matrix}]\\
解得：x_2 = 1~x_1=10
$$



### b.

$$
s_1=12.1~s_2=21.1~s_3=21\\
|\frac{a_{11}}{s_1}| = 0.2504\\
|\frac{a_{21}}{s_2}| = 0.2504\\
|\frac{a_{31}}{s_3}| = 0.2909\\
交换后的矩阵为：\\
[\begin{matrix}
6.11&-14.2&21&-139\\
-3.03&12.1&-7&120\\
3.03&-12.1&14&-119\\
\end{matrix}]\\
一次高斯消元后得到：\\
[\begin{matrix}
6.11&-14.2&21&-139\\
-5.55*10^{-3}&5.071&3.395&51.195\\
5.55*10^{-3}&-5.07&3.605&-70.195\\
\end{matrix}]\\
=>\\
[\begin{matrix}
6.11&-14.2&21&-139\\
0&5.071&3.395&51.195\\
0&-5.071&3.605&-50.195\\
\end{matrix}]\\
E_3+E_2：\\
[\begin{matrix}
6.11&-14.2&21&-139\\
0&5.071&3.395&51.195\\
0&0&7&1\\
\end{matrix}]\\
解得：x_3=0.142~~x_2=10.001~~x_1=0.00527
$$



# Problem4

### a.

​	使用如下代码迭代：

```c
#include<stdio.h>

int main(){
    double x[100][100] = {
        {4,1,-1,5},
        {-1,3,1,-4},
        {2,2,5,1},
    };
    double x1,x2,x3;    
    double xTmp1,xTmp2,xTmp3;
    double sumTmp = 0;
    x1 = x2 = x3 = 0;
    int i=0;
    while(++i<10){
        xTmp1 = (-(x[0][1]*x2+x[0][2]*x3)+x[0][3])/x[0][0];
        xTmp2 = (-(x[1][0]*x1+x[1][2]*x3)+x[1][3])/x[1][1];
        xTmp3 = (-(x[2][0]*x1+x[2][1]*x2)+x[2][3])/x[2][2];
        x1 = xTmp1;
        x2 = xTmp2;
        x3 = xTmp3;
        printf("第%d次迭代:x1=%f,x2=%f,x3=%f\n",i,x1,x2,x3);
    }
}
```

得到的结果为：![image-20211209221333088](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211209221333088.png)



### b.

​	使用如下代码迭代：

```c
#include<stdio.h>

int main(){
    double x[100][100] = {
        {-2,1,0.5,4},
        {1,-2,-0.5,-4},
        {0,1,2,0},
    };
    double x1,x2,x3;    
    double xTmp1,xTmp2,xTmp3;
    double sumTmp = 0;
    x1 = x2 = x3 = 0;
    int i=0;
    while(++i<10){
        xTmp1 = (-(x[0][1]*x2+x[0][2]*x3)+x[0][3])/x[0][0];
        xTmp2 = (-(x[1][0]*x1+x[1][2]*x3)+x[1][3])/x[1][1];
        xTmp3 = (-(x[2][0]*x1+x[2][1]*x2)+x[2][3])/x[2][2];
        x1 = xTmp1;
        x2 = xTmp2;
        x3 = xTmp3;
        printf("第%d次迭代:x1=%f,x2=%f,x3=%f\n",i,x1,x2,x3);
    }
}
```

得到的结果如下：

![image-20211209222632220](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211209222632220.png)

# Problem 5

### a.

​	采用如下代码进行迭代：

```c
#include<stdio.h>
#include<math.h>
#define TOL 0.001

int main(){
    double x[100][100] = {
        {3,-1,1,1},
        {3,6,2,0},
        {3,3,7,4},
    };
    double x1,x2,x3;    
    double xTmp1,xTmp2,xTmp3;
    double sumTmp = 0;
    x1 = x2 = x3 = 0;
    int i=0;
    double maxNorms = 10;
    while(maxNorms > TOL){
        xTmp1 = (-(x[0][1]*x2+x[0][2]*x3)+x[0][3])/x[0][0];
        xTmp2 = (-(x[1][0]*xTmp1+x[1][2]*x3)+x[1][3])/x[1][1];
        xTmp3 = (-(x[2][0]*xTmp1+x[2][1]*xTmp2)+x[2][3])/x[2][2];
        maxNorms = fabs(xTmp1-x1);
        if(fabs(xTmp2-x2)>maxNorms)
            maxNorms = fabs(xTmp2-x2);
        if(fabs(xTmp3-x3)>maxNorms)
            maxNorms = fabs(xTmp3-x3);
        //printf("maxNorms: %f\n",maxNorms);
        x1 = xTmp1;
        x2 = xTmp2;
        x3 = xTmp3;
        i++;
        printf("第%d次迭代:x1=%f,x2=%f,x3=%f\n",i,x1,x2,x3);
    }
    printf("最终迭代结果:x1=%f,x2=%f,x3=%f\n",x1,x2,x3);
}
```

得到的迭代结果为：x1=0.035351,x2=-0.236789,x3=0.657759

![image-20211210004431523](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211210004431523.png)

### b.

​	采用如下代码进行迭代：

```c
#include<stdio.h>
#include<math.h>
#define TOL 0.001

int main(){
    double x[100][100] = {
        {10,-1,0,9},
        {-1,10,-2,7},
        {0,-2,10,6},
    };
    double x1,x2,x3;    
    double xTmp1,xTmp2,xTmp3;
    double sumTmp = 0;
    x1 = x2 = x3 = 0;
    int i=0;
    double maxNorms = 10;
    while(maxNorms > TOL){
        xTmp1 = (-(x[0][1]*x2+x[0][2]*x3)+x[0][3])/x[0][0];
        xTmp2 = (-(x[1][0]*xTmp1+x[1][2]*x3)+x[1][3])/x[1][1];
        xTmp3 = (-(x[2][0]*xTmp1+x[2][1]*xTmp2)+x[2][3])/x[2][2];
        maxNorms = fabs(xTmp1-x1);
        if(fabs(xTmp2-x2)>maxNorms)
            maxNorms = fabs(xTmp2-x2);
        if(fabs(xTmp3-x3)>maxNorms)
            maxNorms = fabs(xTmp3-x3);
        //printf("maxNorms: %f\n",maxNorms);
        x1 = xTmp1;
        x2 = xTmp2;
        x3 = xTmp3;
        i++;
        printf("第%d次迭代:x1=%f,x2=%f,x3=%f\n",i,x1,x2,x3);
    }
    printf("最终迭代结果:x1=%f,x2=%f,x3=%f\n",x1,x2,x3);
}
```

得到的迭代结果为：x1=0.995748,x2=0.957874,x3=0.791575

![image-20211210004616395](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211210004616395.png)
