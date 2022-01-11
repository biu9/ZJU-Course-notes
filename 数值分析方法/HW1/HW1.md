## Problem 1

​	a. 
$$
\frac{1}{2}(f(x_{1}+fx_{2}))∈[f(a),f(b)]\\
存在f(\xi)=\frac{1}{2}(f(x_{1}+fx_{2}))(介值定理)
$$

​	b. 同理
$$
不妨设f(x_2)>f(x_1)\\
\frac{c_{1}f(x_{1})+c_{2}f(x_{2})}{c_1+c_2}≤\frac{c_{1}f(x_{2})+c_{2}f(x_{2})}{c_1+c_2}=f(x_2)≤f(b)
\\同理可以证得，\frac{c_{1}f(x_{1})+c_{2}f(x_{2})}{c_1+c_2}≥f(a)\\
由于满足介值定理，可以找到：\\
f(\xi)=\frac{c_{1}f(x_{1})+c_{2}f(x_{2})}{c_1+c_2}
$$
![image-20211123115936755](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211123115936755.png)
$$
设f(x)=e^x, f(x)∈[0,∞]\\
f(\xi)=\frac{c_{1}f(x_{1})+c_{2}f(x_{2})}{c_1+c_2}等价于\\
\frac{c_1}{c_2}=\frac{f(x_2)-f(\xi)}{f(\xi)-f(x_1)}，等价于\\
\frac{c_1}{c_2}=\frac{DE}{EF}\\
上图给出一个例子，取c_1=2,c_2=1可以找到\frac{DE}{EF}=2的c点
$$

## Problem 2

​	a. 由Mean Value Theorem 
$$
f'(\xi)=\frac{f(b)-f(a)}{b-a}
$$
可以得到 
$$
f'(x_{0}+\xi)=\frac{f(x_{0}+\xi)-f(x_{0})}{\xi}\\

|f(x_{0})-f(x_{0}+\xi)|=f'(x_{0}+\xi)\xi
$$
 绝对误差等于$f'(x_{0})\xi$​, 相对误差等于
$$
\frac{|f(x_{0})-f(x_{0}+\xi)|}{|f(x_{0})|}=
\frac{|f'(x_{0}+\xi)\xi|}{|f(x_{0})|}
$$
​	b. 由于$e^x$的导数是本身，绝对误差等于$5*10^{-6}e^{1+5*10^{-6}}$, 相对误差等于$5*10^{-6}$

​		sinx的导数为cosx，绝对误差等于$5*10^{-6}cos1$,相对误差等于$5*10^{-6}\frac{cos1}{sin1}$

​	c. 对于$e^x$,绝对误差等于$5*10^{-5}e^{10+5*10^-5}$，相对误差等于$5*10^{-5}$

​		对于sinx，绝对误差等于$5*10^{-5}cos10$，相对误差等于$5*10^{-5}\frac{cos10}{sin10}$

## Problem 3

​	a. $\frac{4}{5}+\frac{1}{3}$

​			Ⅰ. exact num = $\frac{17}{15}$

​			Ⅱ. three-digit chopping arithmetic: 0.8+0.333=1.13

​			Ⅲ. three-digit rounding arithmetic: 0.8+0.333=1.13

​			Ⅳ. relative error: $2.94*10^{-3}$

b. $(\frac{1}{3}+\frac{3}{11})-\frac{3}{20}$

​			Ⅰ. exact num = $\frac{301}{660}$

​			Ⅱ. three-digit chopping arithmetic: 0.333+0.272-0.15=0.456

​			Ⅲ. three-digit rounding arithmetic: 0.333+0.273-0.15=0.456

​			Ⅳ. relative error for Ⅱ: $1.32*10^{-4}$

## Problem 4

​	a.考虑定义
$$
|F(x)-c_1L_1-c_2L_2|=|O(x^\alpha)+O(x^\beta)|\\
由于\gamma = min(\alpha,\beta),x->0\\
x^\gamma≥x^\alpha,x^\gamma≥x^\beta\\
|O(x^\alpha)+O(x^\beta)|≤2|O(x^\gamma)\\
|F(x)-c_1L_1-c_2L_2|=|O(x^\alpha)+O(x^\beta)|≤2|O(x^\gamma)|\\
可以得到F(x)=c_1L_1+c_2L_2+O(x^\gamma)
$$
b.
$$
G(x)=F_x(c_1x)+F_2(c_2x)\\
G(x)=L_1+L_2+O(c_1^\alpha x^\alpha)+O(c_2^\beta x^\beta)\\
由于:O(c_1^\alpha x^\alpha)=c_1^\alpha O(x^\alpha)=O(x^\alpha)\\
得到:G(x)=L_1+L_2+O(x^\alpha)+O(x^\beta)\\
由a可以得到：\\
G(x)=L_1+L_2+O(x^\gamma)
$$

## Problem 5

​	a.代码如下：

```c
//bisection method
#include <stdio.h>
#include <math.h>

float function(float x){
    float res = exp(x)-pow(x,2)+3*x-2;
    return res;
}

int main(){
    float a = 0;
    float b = 1;
    float c = (a+b)/2;
    double accuracy = 0.00001;
    int count = 0;
    while(fabs(function(c))>accuracy){
        if(function(a)*function(c)<0){
            b = c;
        }
        else{
            a = c;
        }
        printf("第%d次迭代,求得的解为%lf\n",count++,c);
        c = (a+b)/2;
    }
    printf("%lf",c);
}
```

运行结果如下：

![image-20211124150128528](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211124150128528.png)

​	b.代码如下：

```c
//bisection method
#include <stdio.h>
#include <math.h>

float function(float x){
    float res = x*cos(x)-2*pow(x,2)+3*x-1;
    return res;
}

int main(){
    float a = 0.2;
    float b = 0.3;
    float c = (a+b)/2;
    double accuracy = 0.00001;
    int count = 0;
    while(fabs(function(c))>accuracy){
        if(function(a)*function(c)<0){
            b = c;
        }
        else{
            a = c;
        }
        printf("第%d次迭代,求得的解为%lf\n",count++,c);
        c = (a+b)/2;
    }
    printf("最终解为%lf",c);
}
```

当x∈[0.2,0.3]时，运行结果如下：

![image-20211124151245731](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211124151245731.png)

当x∈[1.2,1.3]时，运行结果如下：

![image-20211124151320282](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211124151320282.png)

## Problem 6

​	a. 代码如下：

```c
//fixed point iteration
#include <stdio.h>
#include <math.h>

float function(float x){
    return -2*sin(M_PI*x);
}

int main(){
    float a = 1;
    float b = 2;
    float c = 1;
    int count = 0;
    while(fabs(function(c)-c)>0.01){
        c=function(c);
        printf("第%d次迭代，求得的解为%f\n",count++,c);
    }
    printf("最终解为:%f\n",c);
    
}
```

运行结果如下：

![image-20211124164118314](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211124164118314.png)

​	b.代码如下：

```c
//fixed point iteration
#include <stdio.h>
#include <math.h>

double function(float x){
    return sqrt(exp(x)/3.0);
}

int main(){
    double a = 1;
    double b = 2;
    double c = 1;
    int count = 0;
    while(fabs(function(c)-c)>0.01){
        c=function(c);
        printf("第%d次迭代，求得的解为%lf\n",count++,c);
    }
    printf("最终解为:%lf\n",c);
    
}
```

运行结果如下：

![image-20211124164335547](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211124164335547.png)

## Problem 7

证明：
$$
|P_n-P|=|g(p_{n-1})-g(p)|=g'(\xi)|p_{n-1}-p|\\
|p_n-p|=g'(\xi)|p_{n-1}-p|\\
由于g'(\xi)>1\\
|p_n-p|>|p_{n-1}-p|...>|p_0-p|\\
因此无法找到不等于p的p_0使得不动点迭代得到的p_n收敛
$$
