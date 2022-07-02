# HW 5

### Problem 1

(1)
$$
\frac{df(x,y,t)}{dt} = k[\frac{d^2f(x,y,t)}{dx^2}+\frac{d^2f(x,y,t)}{dy^2}]\\
f(x,y,0) = f(x,y)\\
当f(x,y) = B_0时,\\
f(x,t) = B_0\\
当f(x,y) = Bcos(wx)sin(wy)时,\\
f(x,y,t) = Bcos(wx)sin(wy)e^{-2Bw^2t}\\
当f(x,y) = Ccos(wx)cos(wy)时\\
f(x,y,t) = Ccos(wx)cos(wy)e^{-2Cw^2t}\\
当f(x,y) = Dsin(wx)sin(wy)时
\\f(x,y,t) = Dsin(wx)sin(wy)e^{-2Dw^2t}\\
当f(x,y) = Esin(wx)cos(wy)时\\
f(x,y,t) = Esin(wx)sin(wy)e^{-2Ew^2t}\\
当f(x,y)是常数,sin(wx)sin(wy),sin(wx)cos(wy),cos(wx)cos(wy),cos(wx)sin(wy)\\
的线性组合时，f(x,y,t)是对应的线性组合
$$
(2)
$$
二维傅里叶级数：\\
f(u,v) = \int_{-∞}^∞ \int_{-∞}^∞ f(x,y)e^{-j2\pi (ux+vy)}dxdy
$$

### Problem 2

$$
x(t) = sin(\pi t),x\in[0,1]\\
x(t) = a_1\phi_1(t)+a_2\phi_2(t)+a_3\phi_3(t)\\
<x(t)·\phi_1(t)> = a_1<\phi_1(t)·\phi_1(t)>\\
\frac{2}{\pi} = a_1·1\\
<x(t)·\phi_2(t)> = a_2<\phi_2(t)·\phi_2(t)>\\
0 = a_2·1,a_2 = 0\\
<x(t)·\phi_3(t)> = a_3<\phi_3(t)·\phi_3(t)>\\
0 = a_3·1,a_3 = 0
$$

### Problem 3

$$
当n=2时，有<\beta_2 ·\beta_1> = 0,\beta_2,\beta_1正交\\
当n>=2时,设n<=m时\{\beta_1,\beta_2...\beta_m\}是正交基\\
当n = m+1时:\\
\beta_{m+1} = a_{m+1} - \sum_{i=1}^{m}\frac{<a_{m+1}·\beta_i>}{<\beta_i·\beta_i>}\beta_i\\
<\beta_{m+1}·\beta_j> = <a_{m+1}·\beta_j>-\sum_{i=1}^{m}\frac{<a_{m+1}·\beta_i>}{<\beta_i·\beta_i>}<\beta_i,\beta_j>\\
 =  <a_{m+1}·\beta_j> - \frac{<a_{m+1}·\beta_j>}{<\beta_j·\beta_j>}<\beta_j,\beta_j> = 0\\
 n = m+1时满足条件，证毕
$$

### Problem 4

(1)
$$
a_1(t) = 1,a_2(t) = t,a_3(t) = t^2,a_4(t) = t^3\\
\beta_1 = a_1(t) = 1\\
\beta_2 = a_2(t) - \frac{<a_2(t)·\beta_1>}{<\beta_1·\beta_1>}\beta_1 = t-\frac{1}{2}\\
\beta_3 = t^2-t+\frac{1}{6}\\
\beta_4 =t^3-\frac{3}{2}t^2+\frac{3}{5}t-\frac{1}{20}
$$
(2)
$$
x(t) = b_1\beta_1(t)+b_2\beta_2(t)+b_3\beta_3(t)+b_4\beta_4(t)\\
<x(t)·\beta_1(t)> = b_1<\beta_1(t)·\beta_1(t)>\\
\frac{1}{6} = b_1·1,b_1 = 0.1666667\\
<x(t)·\beta_2(t)> = b_2<\beta_2(t)·\beta_2(t)>\\
\frac{5}{84} = b_2·\frac{1}{12},b_2 = \frac{5}{7} = 0.71428\\
<x(t)·\beta_3(t)> = b_3<\beta_3t)·\beta_3(t)>\\
\frac{5}{504} = \frac{1}{180}b_3,b_3 =\frac{100}{59} = 1.694915254\\
<x(t)·\beta_4(t)> = b_4<\beta_4(t)·\beta_4(t)>\\
9.9206\times 10^{-4} = b_4·\frac{1}{2800},b_4 = 2.7778\\
b_1 = 0.1666667,b_2 = \frac{5}{7} = 0.71428,b_3 =\frac{100}{59} = 1.694915254,b_4 = 2.7778
$$
(3)

采用如下代码进行拟合，结果如下图

```python
from re import X
from turtle import color
import numpy as np 
import matplotlib.pyplot as plt

'''
beta_1 = 1
beta_2 = t-0.5
beta_3 = t^2-t+1/6
beta_4 = t^3-1.5t^2+0.6t-1/20
b_1 = 0.1666667
b_2 = 0.71428
b_3 = 1.694915245
b_4 = 2.777778
画出y = \sum (b_i*beta_i)
'''

b_1 = 0.1666667
b_2 = 0.71428
b_3 = 1.694915245
b_4 = 2.777778
x =  np.linspace(0,1,1000)
y = b_1*1 + b_2*(x-0.5) + b_3*(x**2-x+1/6) + b_4*(x**3-1.5*x**2+0.6*x-1/20)
y_1 = x**5
plt.plot(x,y,color="red")
plt.plot(x,y_1,color="blue")
plt.show()
```

![image-20220406164615362](HW5.assets/image-20220406164615362.png)

### Problem 5

$$
先证明\{e^{j\frac{2\pi}{N}nk}\}是一组正交基:\\
<e^{j\frac{2\pi}{N}nk}·e^{j\frac{2\pi}{N}nl}> = \sum_{n = 0}^{N-1} e^{j\frac{2\pi}{N}n(k-l)}\\
当k=l时,\sum_{n = 0}^{N-1} e^{j\frac{2\pi}{N}n(k-l)} = N\\
当k≠l时,\sum_{n = 0}^{N-1} e^{j\frac{2\pi}{N}n(k-l)} = \sum_{n=0}^{N-1}cos(\frac{n}{N}2\pi (k-l)) = 0\\
\{e^{j\frac{2\pi}{N}nk}\}是一组正交基\\
x[n] = \sum_{k=0}^{N-1}a_ke^{j\frac{2\pi}{N}nk}\\
<x[n]·e^{j\frac{2\pi}{N}nk}> = a_k·N\\
a_k = \frac{1}{N}\sum_{n = 0}^{N-1}x[n]e^{-j\frac{2\pi}{N}nk}
$$

### Problem 6

(1)
$$
x(t) = \frac{1}{2\pi}\int_{-∞}^∞[x_{cos(w)}cos(wt)+x_{sin(w)}sin(wt)]dw\\
x_{cos(w)} = \int_{-∞}^∞x(t)cos(wt)dt\\
x_{sin(w)} = \int_{-∞}^∞x(t)sin(wt)dt\\
证明:\\
 由于是非周期信号，有:\\
 x(t) = \frac{1}{2\pi}\int_{-∞}^∞X(jw)e^{jwt}dw\\
  = \frac{1}{2\pi}\int_{-∞}^∞X(jw)(cos(wt)+isin(wt))dw\\
  X(jw) = \int_{-∞}^∞x(t)e^{-jwt}dt\\
   = \int_{-∞}^∞x(t)(cos(wt)-isin(wt))dt\\
   代入:\\
   x(t) = \frac{1}{2\pi}\int_{-∞}^∞[(\int_{-∞}^∞x(t)cos(wt)dt)cos(wt)+(\int_{-∞}^∞x(t)sin(wt)dt)sin(wt)]dw\\
   =>x(t) = \frac{1}{2\pi}\int_{-∞}^∞[x_{cos(w)}cos(wt)+x_{sin(w)}sin(wt)]dw
$$
(2)
$$
X(jw) = \int_{-∞}^∞ x(t)e^{-jwt}dt\\
 = \int_{-∞}^∞ x(t)(cos(wt)-isin(wt))dt\\
 X(jw) = x_{cos(w)}-ix_{sin(w)}\\
 x(t) = \frac{1}{2\pi}\int_{-∞}^∞ X(jw)e^{jwt}dw\\
x_{cos(w)} = \int_{-∞}^∞x(t)cos(wt)dt = \frac{1}{2\pi}\int_{-∞}^∞[(\int_{-∞}^∞X(jw)e^{jwt}dw)cos(wt)dt]\\
x_{sin(w)} = \int_{-∞}^∞x(t)sin(wt)dt= \frac{1}{2\pi}\int_{-∞}^∞[(\int_{-∞}^∞X(jw)e^{jwt}dw)sin(wt)dt]\\
$$

### Problem 7

(1)
$$
a_k = \frac{1}{T_0}\int_{T_0}x(t)e^{-jkw_0t}dt\\
a_k = \frac{1}{4}·[\frac{2}{jk\pi}(e^{jk\frac{\pi}{2}}-e^{-jk\frac{\pi}{2}})]\\
 = \frac{sin(k\frac{\pi}{2})}{k\pi}
$$
(2)
$$
x(t) = \sum_{k = -∞}^∞ a_ke^{jkw_0t}\\
 = \sum_{k = -∞}^∞\frac{sin(k\frac{\pi}{2})}{k\pi}e^{jkw_0t}\\
  = lim_{k->0}\frac{sin(k\frac{\pi}{2})}{k\pi}e^{jkw_0t} +\sum_{k = 1}^∞\frac{sin(k\frac{\pi}{2})}{k\pi}e^{jkw_0t}\\
   = \frac{1}{2}+\sum_{k = 1}^∞\frac{sin(k\frac{\pi}{2})}{k\pi}e^{jkw_0t}
$$

##### 吉布斯现象

使用如下代码进行画图

```python
from cProfile import label
import math
from turtle import color
import numpy as np
import matplotlib.pyplot as plt


fig = plt.figure()
n = np.array([5,10,100,1000])
x = np.arange(-10,10,0.01)
for i in n:
    y = []
    for j in np.arange(-10,10,0.01):
        res = 0.5
        for k in np.arange(1,i+1,1):
            tmp = (2*math.sin(k*math.pi/2))/(k*math.pi)*(math.cos(k*math.pi/2*j))
            res += tmp
        y.append(res)
    plt.plot(x,y)
plt.show()
```

N = 5时，图像如下

![image-20220406190535486](HW5.assets/image-20220406190535486.png)

N = 10时

![image-20220406190553386](HW5.assets/image-20220406190553386.png)

N = 100时

![image-20220406190612998](HW5.assets/image-20220406190612998.png)

N = 1000时

![image-20220406190648413](HW5.assets/image-20220406190648413.png)

