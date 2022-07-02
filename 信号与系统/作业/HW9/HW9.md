# HW 9

### 4-5

(1):$3^{-n+1}u[n-1]$
$$
原式=3^{-(n-1)}u[n-1]\\
3^{-n}u[n]<-->\frac{1}{3-e^{-jw}}\\
3^{-(n-1)}u[n-1]<-->e^{-jw}\frac{1}{3-e^{-jw}}
$$
(3):$2^nu[-n]$
$$
2^nu[-n] = (\frac{1}{2})^{-n}u[-n]\\
(\frac{1}{2})^{n}u[n]<-->\frac{1}{1-\frac{1}{2}e^{-jw}}\\
(\frac{1}{2})^{-n}u[-n]<-->\frac{1}{1-\frac{1}{2}e^{jw}}
$$
(5):$\delta[n-2]+\delta[n+2]$

$$
\delta[n]<-->1\\
\delta[n-2]+\delta[n+2]<-->e^{-2jw}+e^{2jw}
$$
(6):$u[n-1]-u[n-5]$
$$
u[n-1]-u[n-5] = u[n+2-3]-u[n-2-3]\\
u[n+2]-u[n-2]<-->\frac{sin(2.5w)}{sin(0.5w)}\\
u[n-1]-u[n-5]<-->e^{-3jw}\frac{sin(2.5w)}{sin(0.5w)}
$$
(9):$n2^{-n}u[n]$
$$
nx[n]<-->j\frac{dX(jw)}{dw}\\
2^{-n}u[n]<-->\frac{1}{1-\frac{1}{2}e^{-jw}}\\
n2^{-n}u[n]<-->-\frac{1}{2}\frac{1}{1-\frac{1}{2}e^{-jw}}
$$
(11):
$$
x[n] = u[n]-u[n-4]\\
 = u[n+2-2]-u[n-2-2]\\
 u[n+2]-u[n-2]<-->\frac{sin(2.5w)}{sin(0.5w)}\\
 x[n]<-->e^{-2jw}\frac{sin(2.5w)}{sin(0.5w)}
$$
(12):
$$
X(e^{jw}) = \sum x[n]e^{-jwn}\\
 = \frac{1}{2}e^{3jw}+e^{2jw}+\frac{3}{2}e^{jw}+2+\frac{1}{2}e^{-3jw}+e^{-2jw}+\frac{3}{2}e^{-jw}\\
  = 2+3cosw+2cos2w+cos3w
$$

### 4-6

(2):
$$
X(e^{jw}) = 1-e^{-jw}+2e^{-j2w}-3e^{-3jw}+4e^{-4jw}\\
\delta[n-n_0]<-->e^{-jwn_0}\\
X(e^{jw})<-->\delta[n]-\delta[n-1]+2\delta[n-2]-3\delta[n-3]+4\delta[n-4]
$$
(3)
$$
X(e^{jw}) = e^{-j\frac{w}{2}},w\in[-\pi,\pi]\\
\frac{sinW_0n}{\pi n}-->X(e^{jw}) = 1(|w|<W_0),X(e^{jw})=0(|w|>W_0),周期为2\pi\\
x[n-\frac{1}{2}]<-->e^{-j\frac{w}{2}}X(e^{jw})\\
x[n] = \frac{sinW_0(n-\frac{1}{2})}{\pi(n-\frac{1}{2})}
$$
(4)
$$
X(e^{jw}) = cos^2w+jsin3w\\
 = \frac{cos2w+1}{2}+jsin3w\\
 = \frac{e^{2jw}+e^{-2jw}+2}{4}+\frac{e^{3jw}-e^{-3jw}}{2}\\
  = \frac{\delta[n-2]+\delta[n+2]+2\delta[n]}{4}+\frac{\delta[n+3]-\delta[n-3]}{2}
$$
(6)
$$
X(e^{jw}) = \frac{1-e^{-jw}}{1-\frac{5}{6}e^{-jw}+\frac{1}{6}e^{-2jw}}\\
X(e^{jw})  =\frac{1-e^{-jw}}{(1-\frac{1}{2}e^{-jw})(1-\frac{1}{3}e^{-jw})}\\
 = \frac{1}{1-\frac{1}{3}e^{-jw}}-(\frac{1}{1-\frac{1}{2}e^{-jw}}-\frac{1}{1-\frac{1}{3}e^{-jw}})\times 3\\
  = 4\frac{1}{1-\frac{1}{3}e^{-jw}}-3\frac{1}{1-\frac{1}{2}e^{-jw}}\\
  x[n] = 4(\frac{1}{3})^nu[n]-3(\frac{1}{2})^nu[n]
$$
(7)
$$
X(e^{jw}) = \frac{1-(2e^{jw})^{-8}}{1-(2e^{jw})^{-1}}\\
 = 1+\sum_{n=1}^7(\frac{1}{2}e^{-jw})^n\\
  = \delta[n] + \sum_{m=1}^7(\frac{1}{2})^m\delta[n-m]
$$

### 4-8

(1)
$$
X(e^{jw}) = \sum x[n]e^{-jwn}\\
X(e^{j0}) = 6
$$
(2)
$$

$$
(3)
$$
x[n] = \frac{1}{2\pi}\int_{2\pi}X(e^{jw})e^{jw}dw\\
x[0] = \frac{1}{2\pi}\int_{2\pi}X(e^{jw})dw = 2\\
\int_{-\pi}^{\pi}X(e^{jw})dw = 4\pi
$$
(4)
$$
X(e^{j\pi}) = \sum x[n]e^{-j\pi n}\\
 = \sum x[n](-1)^n=2
$$
(5)
$$
Re\{X(e^{jw})\}<-->\frac{x[n]+x[-n]}{2}
\\n=7,\frac{x[n]+x[-n]}{2} = \frac{-1}{2}
\\n=6,\frac{x[n]+x[-n]}{2} = \frac{0}{2}
\\n=5,\frac{x[n]+x[-n]}{2} = \frac{1}{2}
\\n=4,\frac{x[n]+x[-n]}{2} = \frac{2}{2}
\\n=3,\frac{x[n]+x[-n]}{2} = \frac{0}{2}
\\n=2,\frac{x[n]+x[-n]}{2} = \frac{0}{2}
\\n=1,\frac{x[n]+x[-n]}{2} = \frac{2}{2}
\\n=0,\frac{x[n]+x[-n]}{2} = \frac{4}{2}
\\n=-1,\frac{x[n]+x[-n]}{2} = \frac{2}{2}
\\n=-2,\frac{x[n]+x[-n]}{2} = \frac{0}{2}
\\n=-3,\frac{x[n]+x[-n]}{2} = \frac{0}{2}
$$
(6)
$$
\int_{-\pi}^{\pi}|X(e^{jw})|^2dw\\
\sum |x[n]|^2 = \frac{1}{2\pi}\int_{-\pi}^{\pi}|X(e^{jw})|^2dw\\
\int_{-\pi}^{\pi}|X(e^{jw})|^2dw = 2\pi \sum |x[n]|^2 = 28\pi
$$
(7)
$$
\int_{-\pi}^{\pi}|\frac{dX(e^{jw})}{dw}|^2dw\\
nx[n]<-->j\frac{dX(e^{jw})}{dw}\\
\int_{-\pi}^{\pi}|\frac{dX(e^{jw})}{dw}|^2dw = -2\pi·\frac{1}{2\pi}\int_{-\pi}^{\pi}|j\frac{dX(e^{jw})}{dw}|^2dw\\
\sum |nx[n]|^2<-->\frac{1}{2\pi}\int_{-\pi}^{\pi}|j\frac{dX(e^{jw})}{dw}|^2dw\\
\int_{-\pi}^{\pi}|\frac{dX(e^{jw})}{dw}|^2dw = 316\pi
$$

### 4-10

(1):
$$
\frac{sin(\pi n /3)}{\pi n}\frac{sin(\pi n /4)}{\pi n}\\
\frac{sin(\pi n /3)}{\pi n}<-->X(e^{jw}) = \left\{
\begin{matrix}
 1 ,|w|<\pi n /3\\
 0 ,|w|>\pi n /3
\end{matrix}
\right.\\
\frac{sin(\pi n /3)}{\pi n}<-->X(e^{jw}) = \left\{
\begin{matrix}
 1 ,|w|<\pi n /4\\
 0 ,|w|>\pi n /4
\end{matrix}
\right.\\
x[n]y[n]<-->\frac{1}{2\pi}\int_{2\pi}X(e^{j\theta})Y(e^{jw-\theta})d\theta =  \left\{
\begin{matrix}
 1/4 ,|w|<\pi  /12\\
 7/24-|w|/2\pi ,|w|\in[\pi/12,7 \pi/12]\\
 0
\end{matrix}
\right.\\
$$
(2)
$$
(n+1)a^nu[n]\\
(n+1)a^nu[n] = na^nu[n]+a^nu[n]\\
nx[n]<-->j\frac{dX(e^{jw})}{dw}\\
a^nu[n]<-->\frac{1}{1-ae^{-jw}}\\
(n+1)a^nu[n]<-->\frac{1-a}{1-ae^{-jw}}
$$
(3)
$$
设x_1[n] =\left\{
\begin{matrix}
\frac{\sqrt E}{N_1-1},|n|<N_1\\
0
\end{matrix}
\right.\\
x[n] = x_1[n]*x_1[n]\\
X(e^{jw}) = X_1(e^{jw})^2 = \frac{E}{(N_1-1)^2}\frac{sin^2(\frac{N_1-1}{2}w)}{sin^2\frac{w}{2}}\\
$$

### 4-13

(1)
$$
x_1[n] = x[1-n]+x[1-n]\\
x[-n]<-->X(e^{-jw})\\
x[n-1]<-->e^{-jw}X(e^{jw})\\
 x[1-n]+x[1-n]<-->2e^{jw}X(e^{-jw})
$$
(2)
$$
x_2[n] = x[-n]cosw_0n,0<w_0<\pi\\
x[n]cosw_0n<-->\frac{1}{2}(X(e^{j(w-w_0)})+X(e^{j(w+w_0)}))\\
x[-n]<-->X(e^{-jw})\\
x[-n]cosw_0n<-->\frac{1}{2}(X(e^{-j(w-w_0)})+X(e^{-j(w+w_0)}))
$$
(3)
$$
x_3[n] = \frac{x^*[-n]+x[n]}{2}\\
x^*[n]<-->X^*(e^{-jw})\\
\frac{x^*[-n]+x[n]}{2}<-->[X^*(e^{jw})+X(e^{jw})]/2
$$
(4)
$$
x_4[n] = (n-1)^2x[n]\\
 = n^2x[n]-2nx[n]+x[n]\\
  = -\frac{dX(e^{jw})}{dw}-2j\frac{dX(e^{jw})}{dw}+X(e^{jw})
$$

### 4-14

(1):$X(e^{jw})$是虚信号，且既不是奇信号也不是偶信号，x[n]是虚信号，且既不是奇信号也不是偶信号

(2):x[n]是实奇信号

(3):x[n]是实信号，且既不是奇信号也不是偶信号

### 4-16

全部满足下列条件之一

### 4-17

$$
X(e^{jw}) = \frac{1}{1-e^{-jw}}(\frac{sin1.5w}{sin0.5w})+3\pi \delta(w),w\in(-\pi,\pi]\\
x_1[n] =\left\{
\begin{matrix}
1,|n|<=1\\
0,|n|>1
\end{matrix}
\right.\\
X_1(e^{jw}) = \frac{sin1.5w}{sin0.5w}\\
\sum^n_{m=-∞} x[m]-->\frac{X(e^{jw})}{1-e^{-jw}}+\pi X(e^{j0})\sum \delta(w-2k\pi)\\
x[n] = \sum_{k=-∞}^n x_1[k]\\
$$

### 4-18

$$
\frac{x[n]-x[-n]}{2}<-->jIm\{X(e^{jw}\} = j[sinw-sin2w]\\
X(e^{jw}) = A+e^{jw}+e^{-2jw}\\
2\pi \sum |x[n]|^2 = \int_{-\pi}^{\pi}|X(e^{jw})|^2dw = 6\pi\\
x[n] = \delta[n]+\delta[n+1]-\delta[n+2]
$$

### 4-19

(1)
$$
y[n] = (\frac{sin\frac{\pi}{4}n}{\pi n})^2*(\frac{sinw_cn}{\pi n})\\
|w_c|<=\pi\\
|w_c|\in[\frac{\pi}{2},\pi]
$$
(2)
$$
y[n] = (\frac{sin\frac{\pi n }{4}}{\pi n}cos(\frac{\pi n}{2}))*(\frac{sinw_cn}{\pi n})\\
|w_c|\in[\frac{3}{4}\pi,\pi]
$$

### 4-20

(b)
$$
X_1(e^{jw}) = [X(e^{j(w+\pi)})+X(e^{j(w-\pi)})]/2\\
x_1[n] = e^{j\pi n}x[n]
$$
(f)
$$
X_5(e^{jw}) = 1-X(e^{j(w-\frac{\pi}{2})})-X(e^{j(w+\frac{\pi}{2})})\\
x_5[n] = \delta[n]-e^{j\frac{\pi}{2}n}x[n]-e^{j\frac{-\pi}{2}n}x[n]
$$

### 4-21

$$
x[n]<-->A(w)+jB(w)\\
Y(e^{jw}) = B(w)+A(w)e^{-jw}\\
\frac{x[n]+x[-n]}{2}<-->A(w)\\
\frac{x[n]-x[-n]}{2}<-->jB(w)\\
y[n] = \frac{x[n-1]+x[-n+1]}{2}-j\frac{x[n]-x[-n]}{2}
$$

### 4-23

### 4-25

(1)
$$
y[n]+\frac{1}{6}y[n-1]-\frac{1}{6}y[n-2] = x[n]-x[n-1]\\
Y(e^{jw})+\frac{1}{6}e^{-jw}Y(e^{jw})-\frac{1}{6}e^{-2jw}Y(e^{jw}) = X(e^{jw})-e^{-jw}X(e^{jw})\\
H(e^{jw}) = \frac{Y(e^{jw})}{X(e^{jw})}\\
 = \frac{1-e^{-jw}}{1+\frac{1}{6}e^{-jw}-\frac{1}{6}e^{-2jw}}
$$
(2)
$$
h[n]<-->H(e^{jw}) =\frac{1-e^{-jw}}{1+\frac{1}{6}e^{-jw}-\frac{1}{6}e^{-2jw}}\\
 =\frac{1-e^{-jw}}{(1+\frac{1}{2}e^{-jw})(1-\frac{1}{3}e^{-jw})}\\
 h[n] = \frac{9}{5}(\frac{-1}{2})^nu[n]-\frac{4}{5}(\frac{1}{3})^nu[n]
$$
(3)
$$
x[n] = 4^{-n}u[n]\\
Y(e^{jw}) = \frac{1-e^{-jw}}{1+\frac{1}{6}e^{-jw}-\frac{1}{6}e^{-2jw}}X(e^{jw})\\
 = \frac{1-e^{-jw}}{1+\frac{1}{6}e^{-jw}-\frac{1}{6}e^{-2jw}}·\frac{1}{1-\frac{1}{4}e^{-jw}}\\
 y[n] = \frac{6}{5}(\frac{-1}{2})^nu[n]+3(\frac{1}{4})^nu[n]-\frac{16}{5}(\frac{1}{3})^nu[n]
$$


### 4-26

$$
(\frac{2}{3})^nu[n]<-->n(\frac{2}{3})^nu[n]
$$

(1)
$$
y[n] = x[n]*h[n]\\
Y(e^{jw}) = X(e^{jw})·H(e^{jw})\\
X(e^{jw}) = \frac{1}{1-\frac{2}{3}e^{-jw}}\\
Y(e^{jw}) = j\frac{dX(e^{jw})}{dw} = -\frac{2}{3}e^{-jw}\frac{1}{(1-\frac{2}{3}e^{-jw})^2}\\
H(e^{jw}) = \frac{Y(e^{jw})}{X(e^{jw})} = \frac{2}{3}e^{-jw}\frac{1}{(1-\frac{2}{3}e^{-jw})}\\
$$
(2)
$$
H(e^{jw}) = \frac{\sum_{k=0}^Mb_ke^{-jkw}}{\sum_{k=0}^Na_ke^{-jkw}} =\frac{2}{3}e^{-jw}\frac{1}{(1-\frac{2}{3}e^{-jw})}\\\\
b_0 = 0,b_1 = \frac{-2}{3}\\
a_0 = 1,a_1 = \frac{-2}{3}\\
y[n]-\frac{2}{3}y[n-1] = \frac{2}{3}x[n-1]
$$

### 4-28

(1):$x[n] = (-1)^n$
$$
x[n]=cos\pi n<--> \pi \sum [\delta(w-\pi)+\delta(w+\pi)]\\
y[n] = x[n]*h[n]\\
Y(e^{jw}) = X(e^{jw})·H(e^{jw}) = 0\\
$$
(2):$x[n] = 1+sin(\frac{3\pi}{8}n+\frac{\pi}{4})+\frac{1}{2}cos(\frac{\pi}{2}n+\frac{\pi}{6})+\frac{1}{4}sin(\frac{2\pi}{3}n+\frac{\pi}{4})$
$$
y[n] = sin(\frac{3\pi}{8}+\frac{\pi}{4})
$$

### 4-32

$$
h_1[n] = \delta[n]-\frac{sin(\pi n /2)}{\pi n}\\
y[n] = (-x[n]*h_1[n]+x[n])*h_3[n]+x[n]*h_1[n]*h_2[n]\\
Y(e^{jw}) = H_3[e^{jw}](-X[e^{jw}]·H_1[e^{jw}]+X[e^{jw}])+X[e^{jw}]·H_1[e^{jw}]·H_2[e^{jw}]\\
 = X[e^{jw}](-H_3(e^{jw})·H_1(e^{jw})+H_3(e^{jw})+H_1[e^{jw}]·H_2[e^{jw})\\
 H(e^{jw}) = -H_3(e^{jw})·H_1(e^{jw})+H_3(e^{jw})+H_1[e^{jw}]·H_2[e^{jw}]\\
 y[n] = 16(\frac{\frac{sinn\pi}{4}}{\pi n})cos\frac{\pi}{2}n
$$

