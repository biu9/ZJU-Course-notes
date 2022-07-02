# HW 6

### 3-5

(1)
$$
e^{-2(t-2)}u(t-2)\\
 = e^{-2jw}·\frac{1}{2+jw}
$$
(3)
$$
\delta(t+\pi)+\delta(t-\pi)\\
 = e^{jw\pi} + e^{-jw\pi}
$$
(5)
$$
x(t) = e^{-t}[u(t) - u(t-1)]\\
设x_1(t) = u(t) - u(t-1) = -[u(t-\frac{1}{2}-\frac{1}{2}) - u(t-\frac{1}{2}+\frac{1}{2})]\\
X_1(t) = -e^{-j\frac{1}{2}w}Sa(\frac{1}{2}w)\\
X(t) = X_1(j(w+1)) = -e^{\frac{1}{2}(w+1)}Sa(\frac{1}{2}j(w+1))
$$

### 3-6

(1)
$$
X(jw) = \pi[\delta(w+3\pi)+\delta(w-2\pi)]\\
x(t) = \frac{1}{2}[e^{-3t}+e^{2t}]
$$

### 3-7

(1)
$$
x_1(t) = x(-t+3)\\
X_1(jw) = X(-jw)e^{-3jw}
$$
(3)
$$
x_2(t) = x_1(3t)\\
X_2(jw) = \frac{1}{3}X(j\frac{1}{3}w)
$$

### 3-8

(2)
$$
e^{-at}cos(w_0t)·u(t)\\
 = cos(w_0t)e^{-at}·u(t)\\
 x_1(t) = e^{-at}·u(t)\\
 X_1(jw) = \frac{1}{a+jw}\\
 x(t) = x_1(t)cos(w_0t) = \frac{1}{2}[X_1(j(w-w_0))+X_1(j(w+w_0))]\\
 X(jw) = \frac{1}{2}[\frac{1}{a-w-1}+\frac{1}{a-w+1}]
$$
(5)
$$
\delta'(t)+2\delta(3-2t)\\
由于\frac{dx(t)}{dt}-->jwX(jw)\\
\delta'(t)-->jw\\
\delta(-2t)-->\frac{1}{2}\\
\delta(3-2t)-->e^{3jw}·\frac{1}{2}\\
\delta'(t)+2\delta(3-2t)-->jw+\frac{1}{2}e^{3jw}
$$
(7)
$$
\frac{sin(\pi t)}{\pi t}\frac{sin(2\pi (t-1))}{\pi (t-1)}\\
设x_1(t) = \frac{sin(\pi t)}{\pi t},X_1(jw) = u(w-\pi)-u(w+\pi)\\
设x_2(t) = \frac{sin(2\pi (t-1))}{\pi (t-1)},X_2(jw) = e^{-jw}[u(w-2\pi) - u(w+2\pi)]\\
x_1(t)·x_2(t) = \frac{1}{2\pi}X_1(jw)*X_2(jw)\\
 = \frac{-j}{2\pi}(1+e^{-jw})[u(w+3\pi) -  u(w+\pi)+u(w-3\pi)-u(w-\pi)]
$$
(8)
$$
x(t) = u(t)+u(t-2)-2u(t-1)\\
u(t)-->\frac{1}{jw}+\pi\delta(w)\\
X(jw) = [\frac{1}{jw}+\pi\delta(w)][1+e^{-2jw}-2e^{-jw}]
$$
(9)
$$
x(t) = \frac{dx_1(t)}{dt}\\
x_1(t) = u(t+1)-u(t-1)-\delta(t+2)-\delta(t-2)\\
X_1(jw) = 2Sa(w)-(e^{2jw}+e^{-2jw})\\
X(t) = \frac{X_1(jw)}{jw} = \frac{2Sa(w)-(e^{2jw}+e^{-2jw})}{jw}
$$

### 3-9

(1)
$$
X(jw) = u(w)-u(w-2)\\
X_1(jw) = u(w+1)-u(w-1)\\
x_1(t) = \frac{sin t}{\pi t}\\
X(jw) = X_1(j(w-1))\\
x(t) = e·\frac{sin t}{\pi t}
$$
(2)

### 3-10

(1)
$$
X(jw) = \frac{2sin3(w-\pi)}{w-\pi}\\
X_1(jw) = \frac{2sin3w}{w}\\
易知x_1(t) = u(t-3)-u(t+3)\\
x(t) = e^{jt\pi}x_1(t) = e^{jt\pi}[u(t-3)-u(t+3)]
$$
(3)
$$
X(jw) = cos(2w+\frac{\pi}{3})\\
 = \frac{e^{j(2w+\frac{\pi}{3})} + e^{-j(2w+\frac{\pi}{3})}}{2}\\
 = \frac{e^{j\frac{\pi}{3}}\delta(t+2)+e^{-j\frac{\pi}{3}}\delta(t-2)}{2}
$$

### 3-11

$$
x(t) = cosw_0t ·(1-\frac{2}{\tau_1}|t|),|t|<\frac{\tau_1}{2}\\
设x_1(t) = cosw_0t,X_1(jw) = \delta(t+w_0)\\
设x_2(t) = 1-\frac{2}{\tau_1}|t|\\
x_3(t) = u(t+\frac{\tau_1}{4})-u(t-\frac{\tau_1}{4})\\
x_2(t) = x_3(t) * x_3(t)\\
X_2(jw) = X_3(jw)^2 = (\frac{\tau_1}{2}Sa(\frac{\tau_1}{4}w))^2\\
X(jw) = \frac{1}{2\pi}·X_1(jw)*X_2(jw)\\
 = \frac{1}{2\pi}·[\frac{\tau_1}{2}Sa(\frac{\tau_1}{4}(w-w_0))]^2
$$

### 3-13

$$
x_2(t) = x(1-t)+x(1+t)\\
x(t) = \sum a_ke^{jkw_0t}\\
x_2(t) = \sum a_ke^{jkw_0(1-t)} + \sum a_ke^{jkw_0(1+t)}
$$

### 3-14

(1)

由于实数信号的傅里叶变换的实部是偶函数，虚部是奇函数，$x_2(t),x_3(t)$是实值函数

(2)

当x(t)是实值偶函数时，其频谱也是实值偶函数，$x_2(t)$是实值偶函数

### 3-15

$$
当|k|>1时，a_k = 0\\
x(t) = a_0+a_1e^{-jw_0t}+a_{-1}e^{jw_0t}\\
由于x(t)是实值偶函数,a_k = a_{-k}\\
x(t) = a_0 + a_1(e^{jw_0t}+e^{-jw_0t}) = a_0+2a_1cos\pi t\\
\frac{1}{2}\int_0^2|x(t)|^2dt = \frac{1}{2}\int_0^2|a_0^2+4a_1^2cos^2\pi t+4a_0a_1cos\pi t|dt = 1\\
a_0^2+2a_1^2 = 1\\
x(t) = 1或x(t) = \sqrt2cos(\pi t)
$$

### 3-16

$$
(2+jw)X(jw)<-^F->2x(t)+\frac{dx(t)}{dt} = Ae^{-t}u(t)...(1)\\
\frac{1}{2\pi}\int_{-∞}^∞|X(jw)|^2dw = \int_{-∞}^∞|x(t)|^2dt = 1...(2)\\
由(1)式可以解得:\\
x(t) = A(e^{-t} - e^{-2t})u(t)\\
代入(2)式,解得A=2\sqrt3\\
x(t) = 2\sqrt 3(e^{-t} - e^{-2t})u(t)
$$

### 3-17

$$
x(t)是实值信号,则X(jw)的实部是偶函数\\
\frac{1}{2\pi}\int_{-∞}^∞Re\{X(jw)\}e^{jwt}dw = e^{-|t|}\\
\frac{1}{2\pi}\int_{-∞}^∞Re\{X(jw)\}e^{jwt}dw = \frac{1}{2\pi} \int_{-∞}^∞Re\{X(jw)\}cos(wt)dw = e^{-|t|}\\
\int_{0}^∞Re\{X(jw)\}cos(wt)dw = \pi e^{-|t|}\\
Re\{X(jw)\} = \frac{x(t)+x(-t)}{2}\\
=>\int_{0}^∞x(t)cos(wt)dw = 2\pi e^{-|t|}\\
x(t) = 2e^{-t}u(t)
$$

### 3-18

(1)
$$
x(t) = E[u(t+\frac{\tau}{2}-\frac{\tau}{2})-u(t-\frac{\tau}{2}-\frac{\tau}{2})]\\
设x_1(t) = E[u(t+\frac{\tau}{2})-u(t-\frac{\tau}{2})]\\
X_1(jw) = \tau ESa(\frac{\tau}{2}w)\\
X(jw) = e^{-jw\frac{\tau}{2}}\tau ESa(\frac{\tau}{2}w)\\
\theta(w) = \frac{-\tau w}{2}
$$
(2)
$$
X(0) = \tau E Sa(0) = \tau E
$$
(3)
$$
x(t) = \frac{1}{2\pi}\int_{-∞}^∞X(jw)e^{jwt}dw\\
\int_{-∞}^∞X(jw)dw = 2\pi x(0) = 2\pi E
$$
(4)
$$
\int_{-∞}^∞X(jw)\frac{2sin w}{w}e^{i2w}dw...(1)\\
设X_1(jw) = \frac{2sin w}{w}e^{i2w}\\
X_2(jw) = X_1(jw)X(jw)\\
\int_{-∞}^∞X(jw)\frac{2sin w}{w}e^{i2w}dw =2\pi x_2(t)\\
x_2(t) = x(t)*x_1(t)\\
当\tau<1时，(1)式=0\\
当\tau \in[1,3]时，(1)式=2\pi E(\tau - 1)\\
当\tau ≥3时，(1)式=4\pi E
$$
(5)
$$
\int |X(jw)|^2dw = 2\pi \int |x(t)|^2dt = 2\pi \tau E^2
$$
(6)

$$
Re\{X(jw)\}<-^F->\frac{x(t)+x(-t)}{2}\\
 = \frac{E}{2}[x(t+\tau) - x(t-\tau)]\\
 
$$
![image-20220414221947399](HW6.assets/image-20220414221947399.png)

