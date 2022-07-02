# HW 3

### 2-3

$x_1(t) = u(t+1)-u(t-1),x_2(t) = \delta(t+5)+\delta(t-5),x_3(t) = \delta(t+\frac{1}{2})+\delta(t-\frac{1}{2})$

(1):$x_1(t)*x_2(t)$

$$
由于有x(t+t_0)*h(t-t_0) = x(t)*h(t),x(t)*\delta(t) = x(t)\\
[u(t+1)-u(t-1)]*[\delta(t+5)+\delta(t-5)] \\= 
\delta(t+5)*x_1(t)+\delta(t-5)*x_1(t)\\
 = x_1(t-5) + x_1(t+5)
$$
(2):$x_1(t)*x_2(t)*x_3(t)$
$$
由第一小题，x_1(t)*x_2(t)*x_3(t) = [x_1(t+5)+x_1(t-5)]*x_3(t)\\
 = x_1(t+5)*x_3(t)+x_1(t-5)*x_3(t)\\
 x_1(t+5)*x_3(t) = x_1(t+5)*\delta(t+\frac{1}{2})+x_1(t+5)*\delta(t-\frac{1}{2})\\
  = x_1(t+\frac{1}{2})+x_1(t-\frac{1}{2})\\
  同理，x_1(t-5)*x_3(t) = x_1(t+\frac{1}{2})+x_1(t-\frac{1}{2})\\
  x_1(t)*x_2(t)*x_3(t) =2[x_1(t+\frac{1}{2})+x_1(t-\frac{1}{2})]
$$
(3):$x_1(t)*x_3(t)$
$$
x_1(t)*x_3(t) = x_1(t)*\delta(t+\frac{1}{2})+x_1(t)*\delta(t-\frac{1}{2})\\
 =x_1(t+\frac{1}{2})+x_1(t-\frac{1}{2})
$$

### 2-4

  $y(t) = e^{-t}u(t)*\sum \delta(t-3k)$
$$
证明：\\
y(t) = \sum e^{-t}u(t)*\delta(t-3k)\\
 = \sum e^{-(t-k)}u(t-3k)~~~...1\\
 由于0<t≤3\\
 1式等价于\sum_{k=-∞}^{0} e^{-(t-3k)}\\
  = \frac{e^{-t}}{1-e^{-3t}}\\
  A = \frac{1}{1-e^{-3t}}
$$

### 2-5

(a)

![image-20220317210932155](HW3.assets/image-20220317210932155.png)

(b)

![image-20220317211133197](HW3.assets/image-20220317211133197.png)

(c)

![image-20220317213024932](HW3.assets/image-20220317213024932.png)

(d)

![image-20220321105727815](HW3.assets/image-20220321105727815.png)

(e)
$$
y(t)=-2t^2-2t,t\in[-1,0]\\
y(t)=2t^2-2t,t\in[0,1]\\
且y(t)以2为周期
$$
![image-20220321122315391](HW3.assets/image-20220321122315391.png)

### 2-8

(1)
$$
x(t) = 3x_0(t),h(t) = h_0(t)\\
y(t) = 3x_0(t)*h_0(t) = 3y_0(t)
$$
![image-20220321123148624](HW3.assets/image-20220321123148624.png)

(3)
$$
x(t) = x_0(t-2),h(t) = h_0(t+1)\\
y(t) = x_0(t-2)*h_0(t+1) =y_0(t-1)
$$
(5)
$$
x(t) = \frac{dx_0(t)}{dt},h(t) = h_0(t)\\
y(t) = \frac{dy_0(t)}{dt}
$$
![image-20220321124647090](HW3.assets/image-20220321124647090.png)

### 2-9

$$
h_1[n] = a^nu[n]+\beta^nu[n]\\
h_2[n] = (-\frac{1}{2})^nu[n]\\
x[n] = \delta[n]+\frac{1}{2}\delta[n-1]\\
y[n]=h_1[n]*h_2[n]*x[n]\\
y[n] = [(a^nu[n]+\beta^nu[n])*((-\frac{1}{2})^nu[n])*(\delta[n]+\frac{1}{2}\delta[n-1])]\\
 = [\frac{1-(-\frac{1}{2}a)^{n+1}}{1+\frac{1}{2}a}u[n]+\frac{1-(-\frac{1}{2}\beta)^{n+1}}{1+\frac{1}{2}\beta}u[n]]*(\delta[n]+\frac{1}{2}\delta[n-1]))\\
  = \frac{1-(-\frac{1}{2}a)^{n+1}}{1+\frac{1}{2}a}u[n]+\frac{1-(-\frac{1}{2}\beta)^{n+1}}{1+\frac{1}{2}\beta}u[n]+\frac{1}{2}u[n-1][\frac{1-(-\frac{1}{2}a)^{n}}{1+\frac{1}{2}a}+\frac{1-(-\frac{1}{2}\beta)^{n}}{1+\frac{1}{2}\beta}]
$$

### 2-10

$$
y[n]=x_1[n]*x_1[n]*x_3[n]\\
x_1[n]=(0.5)^nu[n],x_2[n] = u[n+3],x_3[n] = \delta[n]-\delta[n-1]\\
$$

(1)求$x_1[n]*x_2[n]$
$$
x_1[n]*x_2[n] = (0.5)^nu[n]*u[n+3]\\
 = \sum_{k=-∞}^{∞} (0.5)^nu[k]\times u[n-k+3]\\
  =(\sum_{k=0}^{n+3}(0.5)^n)u[n+3]\\
   = (2-0.5^{n+3})u[n+3]
$$
(2)求$x_1[n]*x_2[n]*x_3[n]$
$$
x_1[n]*x_2[n]*x_3[n]\\
 = (2-0.5^{n+3})u[n+3]*(\delta[n]-\delta[n-1])\\
  = (2-0.5^{n+3})u[n+3]-(2-0.5^{n+2})u[n+2]
$$
(3)求$x_2[n]*x_3[n]$
$$
x_2[n]*x_3[n] =u[n+3]*(\delta[n]-\delta[n-1])\\
 = u[n+3]-u[n+2] = \delta[n+3]
$$

### 2-11

(1)
$$
h[n] = h_1[n]*h_2[n]-h_1[n]*h_3[n]*h_4[n]+h_5[n]
$$
(2)
$$
h_1[n] = 4(\frac{1}{2})^n(u[n]-u[n-3])\\
h_2[n] = h_3[n] = (n+1)u[n]\\
h_4[n] = \delta[n-1]\\
h_5[n] = \delta[n]-4\delta[n-3]\\
h[n] = h_1[n]*h_2[n]-h_1[n]*h_3[n]*h_4[n]+h_5[n]\\
 = h_1[n]*(h_2[n]-h_2[n-1])+h_5[n]\\
  = h_1[n]*(u[n])+h_5[n]\\
   = [(8-(\frac{1}{2})^{n-2})u[n]]-[(8-(\frac{1}{2})^{n+1})u[n+3]]+h_5[n]\\
   
$$
![image-20220321152112464](HW3.assets/image-20220321152112464.png)

(3)



### 2-12

$$
y(t) = \int_{-∞}^te^{-(t-\tau)}x(\tau-2)d\tau\\
$$

(1)
$$
单位冲激响应：\\
y(t) = \int_{-∞}^te^{-(t-\tau)}x(\tau-2)d\tau\\
 =\int_{-∞}^te^{-(t-\tau)}\delta(\tau-2)d\tau\\
  h(t) = e^{-t+2}u(t-2)
$$
(2)
$$
x(t) = -u(t-2)+u(t+1)\\
y(t) = \int_{-∞}^te^{-(t-\tau)}x(\tau-2)d\tau\\
 =\int_{-∞}^te^{-(t-\tau)}[-u(\tau-4)+u(\tau-1)]d\tau\\
  = -(1-e^{4-t})u[t-4]+(1-e^{1-t})u[t-1]
$$

### 2-13

(1)
$$
h(t) = h_1(t)+h_2(t)*h_3(t)*h_1(t)\\
 = u(t)+u(t)*\delta(t-1)*-\delta(t)\\
  = u(t)-u(t-1)\\
$$
(2)
$$
x(t)=u(t+1)-u(t-2)\\
y(t)=x(t)*h(t)=[u(t+1)-u(t-2)]*[u(t)-u(t-1)]\\
 =(t+1)u(t+1)-tu(t)-(t-2)u(t-2)+(t-3)u(t-3)
$$

### 2-14

(1)$h(t) = e^{-4t}u(t-2)$

因果性：当t<0时，有h(t)=0;因此h(t)是因果的

稳定性：$\sum |h(t)| = \sum_{t=2}^{∞} e^{-4t}$，有界，h(t)是稳定的

(3)$h(t) = e^{-2t}u(t+50)$

因果性：当t<0时，存在t使得h(t)>0;h(t)是非因果的

稳定性：$\sum |{h(t)}| = \sum_{t=-50}^∞e^{-2t}$，有界，h(t)是稳定的

(5)$h(t) = e^{-6|t|}$

因果性：当t<0时，有h(t)>0;因此h(t)是非因果的

稳定性：$\sum |{h(t)}| =2\sum_{t=0}^∞e^{-6t} $，有界，h(t)是稳定的

### 2-15

(1)$h[n] = 0.2^nu[n]$

因果性：当n<0时，有h[n]=0;h[n]是因果的

稳定性：$\sum |h[n]| = \sum_{n=0}^∞0.2^n$，有界，h[n]是稳定的

(3)$h[n] = (-0.5)^nu[-n]$

因果性：当n<0时，h[n]≠0;h[n]是非因果的

稳定性：$\sum |h[n]| = \sum_{n=-∞}^00.5^n$，无界，h[n]是不稳定的

(5)$(-\frac{1}{2})^nu[n]+(1.01)^nu[n-1]$

因果性：当n<0时，h[n]=0;h[n]是因果的

稳定性：$\sum |h[n]| = \sum_{n=0}^∞0.5^n+\sum_{n=1}^∞1.01^n$，无界，h[n]是不稳定的

(7)$h[n] = n(\frac{1}{3})^nu[n-1]$

因果性：当n<0时，h[n]=0;h[n]是因果的

稳定性：$\sum |h[n]| = \sum_{n=1}^∞\frac{n}{3^n}$，有界，h[n]是稳定的

### 2-16

(1)

正确，若$lim_{t->∞}|h(t)|=c,则有\sum |h(t)|->∞;与系统稳定矛盾$

(2)

正确，$\sum |h(t)|>\sum |h(t)|;设一个周期内的\sum |h(t)| = c>0;则有\sum |h(t)| = \sum c->∞;h(t)不稳定$

(3)

错误

$\delta(t+1)*\delta(t-1) = \delta(t),\delta(t-1)因果，\delta(t+1)非因果$

(4)

错，$\sum |h[n|≤\sum k->∞;无法证明收敛,以h[n]为单位脉冲响应的系统不一定稳定$

(5)

正确，由于h[n]的长度有限且有界，不妨设该长度为从0到k$\sum h|n|<\sum_{0}^k|h[n|$，有界，h[n]稳定

(6)

错误，系统因果无法推出系统稳定

(7)

错误
$$
h(t) = h_1(t)*h_2(t),当t<0时,h(t) = \int_{-∞}^∞h_2(\tau)\times h_1(t-\tau)d\tau\\
 设h_2(t)是因果的\\
 h(t) = \int_{0}^∞h_2(\tau)\times h_1(t-\tau)d\tau\\
 当h_2(t)=0时，h(t)=0,此时h(t)因果
$$
(8)

错误，是充分不必要条件

(9)

正确·，是定义

### 2-18

$$
x_1(t) = u(t)-u(t-2)\\
y_1(t) = h(t)*x_1(t)\\
易知,h(t) = u(t)-u(t-1)\\
y_2(t) = [u(t)-u(t-1)]*sin\pi t[u(t)-u(t-1)]\\
y_2(t) = \frac{1-cos\pi t}{\pi}[u(t)-u(t-2)]
$$

