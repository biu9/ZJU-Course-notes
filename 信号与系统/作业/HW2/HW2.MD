# HW 2

### 1-7(4)

$f(t)[\delta(t+1)+\delta(t-2)]$

当t=-1或t=2时，$\delta(t+1)+\delta(t-2) = 1$,其余时刻等于0，故图像如下：

![image-20220310140525082](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220310140525082.png)

### 1-10(4)

$x[n-3]\delta[n-3]$

当且仅当n=3时，$\delta[n-3]=1$

![image-20220310144746953](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220310144746953.png)

### 1-20

(1):
$$
\int_{-4}^4(t^2+3t+2)[\delta(t)+\delta(t-1)]dt\\
由于有x(t)\delta(t) = x(0)\delta(t)，原式等于\\
=>(t^2+3t+2)[\delta(t)] = 2\delta(t)\\
[(t-1)^2+5(t-1)+6]\delta(t-1) = 6\delta(t-1)\\
\int_{-4}^4(t^2+3t+2)[\delta(t)+\delta(t-1)]dt\\
 = \int_{-4}^{4}2\delta(t)+6\delta(t-1)dt\\
  = 8
$$
(2):
$$
\int_{-\pi}^{\pi}(1-cost)\delta(t-\frac{\pi}{2})dt\\
-cost ·\delta(t-\frac{\pi}{2}) = sin(t-\frac{\pi}{2})\delta(t-\frac{\pi}{2}) = 0\\
\int_{-\pi}^{\pi}(1-cost)\delta(t-\frac{\pi}{2})dt\\
 = \int_{-\pi}^{\pi}\delta(t-\frac{\pi}{2})dt = 1
$$
(3):
$$
\int_{-2\pi}^{2\pi}(1+t)\delta(cost)dt\\
当t=\frac{\pi}{2},\frac{3\pi}{2},-\frac{\pi}{2},-\frac{3\pi}{2}时，\delta(cost) = 0\\
\int_{-2\pi}^{2\pi}(1+t)\delta(cost)dt\\
 = 1+\frac{\pi}{2}+1+\frac{3\pi}{2}+1+-\frac{\pi}{2}+1+-\frac{3\pi}{2}\\
  = 4
$$

### 1-22

$$
输入x(t) = u(t)时，y(t) = e^{-t}u(t)+u(-1-t)\\
图1-71的输入是x_1(t) = u(t-1)-u(t-2)\\
x_1(t) = x(t-1)-x(t-2)\\
y_1(t) = y(t-1)-y(t-2)\\
y_1(t) = e^{-t+1}u(t-1)+u(-t)-e^{-t-2}u(t-2)-u(1-t)
$$

### 1-28

$$
x_1(t) = u(t),y_1(t) = e^{-at}u(t)\\
x_2(t) = \delta(t) = \frac{du(t)}{dt} = \frac{dx_1(t)}{dt}\\
y_2(t) = \frac{dy_1(t)}{dt} = e^{-at}\delta(t)-ae^{-at}u(t)
$$

### 2-2

$x[n]*h[n] = \sum x[k]h[n-k]$

(1):
$$
x[n] = nu[n],h[n]=\delta[n-2]\\
y[n] = x[n]*h[n] = \sum x[k]h[n-k]\\
 = \sum ku[k]\delta[n-2-k]\\
 当k=n-2时，\delta[n-2-k] = 1\\
 y[n] = (n-2)u[n-2]
$$
(2):
$$
x[n] = 2^nu[n],h[n] = u[n]\\
y[n] = x[n]*h[n] = \sum x[k]h[n-k]\\
 = \sum 2^ku[k]u[n-k]\\
 当k∈[0,n]时，u[k]u[n-k] = 1\\
 y[n] = \sum_{k=0}^{k=n}2^k\\
  = 2^{n+1}-1
$$
(3):
$$
x[n] = 2^nu[-n-1],h[n] = \frac{1}{2^n}u[n-1]\\
y[n] = \sum 2^ku[-k-1]·\frac{1}{2^{n-k}}u[n-k-1]\\
当k<min(-1,n-1)时，u[-k-1]u[n-k-1] = 1\\
y[n] = \sum_{k=-∞}^{k=min(-1,n-1)}2^{2k-n}\\
y[n] = \frac{2^{-|n|}}{3}
$$
(4):
$$
x[n] = a^nu[n],h[n] = \beta^nu[n]\\
y[n] = \sum a^ku[k]\beta^{n-k}u[n-k]\\
当k∈[0,n]时，u[k]·u[n-k] = 1\\
y[n] = \sum_{k=0}^{k=n}a^k\beta^{n-k}\\
y[n] = \frac{\beta^{n+1}-a^{n+1}}{\beta-a}u[n]
$$
(5):
$$
x[n] = (-1)^n(u[-n]-u[-n-8]),h[n] = u[n]-u[n-8]\\
y[n] = \sum (-1)^k(u[-k]-u[-k-8])(u[n-k]-u[n-k-8])\\
y[n] = \sum (-1)^{k}(u[-k]u[n-k]-u[-k]u[n-k-8]-u[-k-8]u[n-k]+u[-k-8]u[n-k-8])\\
 = \sum_{k=-∞}^{k=min(0,n)} (-1)^ku[n]-\sum_{k=-∞}^{k=min(0,n-8)}(-1)^ku[n-8]-\sum_{k=-∞}^{k=min(n,-8)}(-1)^ku[n+8]+\sum_{k=-∞}^{k=min(n-8,-8)}(-1)^ku[n]\\
   = \frac{1-(-1)^{n}}{2}(2u[n-1]-u[n+7]-u[n-9])
$$

### 选做题

##### 1.

1-1 证明 $x(t)\delta(t-t_0) = x(t_0)\delta(t-t_0)$
$$
由于\int x(t)\delta(t)dt = x(0)\\
\int x(t)\delta(t-t_0)dt = x(t_0)\\
\int x(t_0)\delta(t-t_0)dt = x(t_0)\int \delta(t-t_0)dt = x(t_0)\\
\int x(t)\delta(t-t_0)dt = \int x(t_0)\delta(t-t_0)dt\\
x(t)\delta(t-t_0) = x(t_0)\delta(t-t_0)
$$
1-2 证明$\delta(at+b) = x = \frac{1}{|a|}\delta(t+\frac{b}{a})$
$$
由于有\delta(at) = \frac{1}{|a|}\delta(t)\\
\int y(t+\frac{b}{a})\delta(at+b)dt = \int y(\frac{at+b}{a})\delta(at+b)d(\frac{at}{a})\\
 = \frac{1}{|a|}\int y(\frac{at+b}{a})\delta(at+b)d(at+b)\\
  = \frac{1}{a}y(0)\\
  \int \frac{1}{|a|}\delta(t+\frac{b}{a})y(t+\frac{b}{a})d(t+\frac{b}{a})\\
   = \frac{1}{|a|}y(0)
   \\
   \int \delta(at+b)  = \int \frac{1}{|a|}\delta(t+\frac{b}{a})
   \\
   =>\delta(at+b) = x = \frac{1}{|a|}\delta(t+\frac{b}{a})
$$

## 编程作业

### 一维卷积

使用`cov_1d.py`中的代码进行卷积，得到如下结果

![image-20220314213518343](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220314213518343.png)

由于精度的问题，部分结果与使用`numpy`自带的卷积函数得到的结果不同

#### 运行时间复杂度

运行结果如下：

![image-20220314214731922](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220314214731922.png)

python自带的卷积函数运行速度远远快于自己编写的卷积函数，部分原因如下

- python的numpy库底层使用c编写
- python自带的卷积函数使用的算法的时间复杂度是O(nlog n)
- python自带的卷积函数采取了并行化加速

### 二维卷积

运行`conv_2d_tmp.py`中的文件，得到如下结果

![image-20220314213939069](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220314213939069.png)

##### 图片卷积

使用第一个卷积核得到的图片如下

![myImg1](F:\桌面\一些文件\主修课程\大二下\信号与系统\作业\HW2\myImg1.jpg)

使用第二个卷积核得到的图片如下，有一定的边缘提取的效果

![myImg2](F:\桌面\一些文件\主修课程\大二下\信号与系统\作业\HW2\myImg2.jpg)

