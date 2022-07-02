# HW 7

### 3-19

$$
H(jw) = \frac{sin3w}{w}cosw\\
设H_1(jw) = \frac{sin3w}{w}\\
h_1(t) = \frac{1}{2}[u(t+3)-u(t-3)]\\
H_2(jw) = cosw\ = \frac{e^{jw}+e^{-jw}}{2}\\
h_2(t) = \frac{\delta(t+1)+\delta(t-1)}{2}\\
h(t) = h_1(t)*h_2(t) = \frac{1}{4}[u(t+4)+u(t+2)-u(t-2)-u(t-4)]
$$

### 3-20

$$
H(jw) = \frac{1}{jw+3}\\
对于x(t),y(t) = e^{-3t}u(t)-e^{-4t}u(t)\\
y(t) = x(t)*h(t)\\
Y(jw) = X(jw)·H(jw) = \frac{1}{3+jw}-\frac{1}{4+jw}\\
X(jw)·\frac{1}{3+jw} = \frac{1}{3+jw}-\frac{1}{4+jw}\\
X(jw) = \frac{1}{4+jw}\\
x(t) = e^{-4t}u(t)
$$

### 3-23

(1)
$$
x(t) = e^{-t}u(t),h(t) = e^{-3t}u(t)\\
y(t) = x(t)*h(t)\\
Y(jw) = X(jw)·H(jw)\\
Y(jw) = \frac{1}{(1+jw)(3+jw)}\\
 = \frac{1}{2}[\frac{1}{1+jw} - \frac{1}{3+jw}]\\
 y(t) = \frac{e^{-t}u(t) - e^{-3t}u(t)}{2}
$$
(2)
$$
x(t) = te^{-t}u(t),h(t) = e^{-3t}u(t)\\
y(t) = x(t)*h(t)\\
Y(jw) = X(jw)·H(jw)\\
Y(jw) = \frac{1}{3+jw}·\frac{1}{(1+jw)^2}\\
y(t) = \frac{1}{4}(2te^{-t}-e^{-t}+e^{-3t})
$$

### 3-24*

(1)
$$
y(t) = x(t)p(t) = \sum a_kx(t)e^{jw_0kt}\\
Y(jw) = \sum a_kX(j(w-w_0k))
$$
2-1
$$
p(t) = cos\frac{t}{2} = \frac{e^{jt/2}+e^{-jt/2}}{2}\\
y(t) = p(t)x(t)\\
Y(jw) = \frac{1}{2}[X(j(w-\frac{1}{2}))+X(j(w+\frac{1}{2}))]\\
图像如下：
$$
![image-20220421161900729](HW7.assets/image-20220421161900729.png)

2-4
$$
p(t) = \sum \delta(t-\pi k)
\\
 = \frac{1}{2\pi}\sum e^{j2kt}\\
y(t) = x(t)p(t)\\
 = \frac{1}{2\pi}\sum x(t)e^{j2kt}\\
Y(jw) = \frac{1}{2\pi}\sum X(j(w-2k))
$$
2-6
$$
p(t) = \sum \delta(t-4\pi k)\\
 = \frac{1}{4\pi}\sum e^{j\frac{k}{2}t}\\
y(t) = x(t)p(t)\\
 = \frac{1}{4\pi}\sum x(t)e^{j\frac{k}{2}t}\\
 Y(jw) = \frac{1}{4\pi}\sum X(j(w-\frac{k}{2}))
$$

### 3-26

> 证明LTI系统对周期信号的响应仍然是周期信号且不会产生新的谐波分量或新的频率分量

$$
设输入为x(t)\\
由于x(t)是周期函数，x(t) = \sum a_ke^{jkw_0t}\\
y(t) =  x(t)*h(t)\\
Y(jw) = X(jw)·H(jw)\\
 = \sum2\pi a_k \delta(w-kw_0)H(jw)\\
 y(t)可以写为\sum a_{k1}e^{jkw_0t},仍然是周期信号且不会产生新的谐波分量或新的频率分量\\
$$



### 3-27

(1)
$$
h(t) = \frac{sin5(t-1)}{\pi(t-1)}\\
x(t) = cos(7t+\frac{\pi}{3})\\
y(t) = x(t)*h(t)\\
Y(jw) = X(jw)H(jw)\\
H(jw) = e^{-5jw}[u(w+5) - u(w-5)]\\
x(t) = cos(7t+\frac{\pi}{3}) = \frac{1}{2}cos7t-\frac{\sqrt3}{2}sin7t\\
X(jw) = \frac{1}{2}\pi [\delta(w+7)+\delta(w-7)]-\frac{\sqrt3}{2}\frac{\pi}{j}[\delta(w+7) - \delta(w-7)]\\
Y(jw) = 0\\
y(t) = 0
$$
(3)
$$
h(t) = \frac{sin5(t-1)}{\pi(t-1)}\\
x(t) = \frac{sin5(t+1)}{\pi(t+1)}\\
Y(jw) = H(jw)X(jw)\\
H(jw) = e^{-5jw}[u(w+5) - u(w-5)]\\
X(jw) = e^{5jw}[u(w+5) - u(w-5)]\\
Y(jw) = u(w+5) - u(w-5)\\
y(t) = \frac{sin5t}{\pi t}
$$

### 3-33

$$
H(jw) = [u(w+(w_0+w_c))-u(w-(w_0+w_c))] - [u(w+(w_0-w_c)) - u(w-(w_0-w_c))] \\
h(t)<-^F->H(jw)\\
h(t) = \frac{sin((w_0+w_c)t)}{\pi t} - \frac{sin((w_0-w_c)t)}{\pi t}\\
由于h(t)是非因果的，该滤波器在时域上不可行
$$

### 3-34

$$
y(t) = x(t)*h(t)\\
Y(jw) = X(jw)H(jw)\\
x(t) = 2E[u(t)-2u(t-T)+2u(t-2T)-u(t-3T)]\\
H(jw) = e^{-jwt_0}\\
h(t) = \frac{w_c}{\pi}\frac{sin[w_c(t-t_0)]}{w_c(t-t_0)}\\
低通滤波器的阶跃响应为s(t) = \frac{1}{2}+\frac{1}{\pi}Si[w_c(t-t_0)]\\
Si(y) = \int_0^y \frac{sinx}{x}dx\\
y(t) = x(t)*h(t)\\
 = \frac{2E}{\pi}[Si[w_c(t-t_0)]-2Si[w_c(t-t_0-T)]+2Si[w_c(t-t_0-2T)]-Si[w_c(t-t_0-3T)]]
$$

