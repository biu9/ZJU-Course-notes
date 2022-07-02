# HW1

### Problem 1

(a):
$$
E_1 = zcos(wt-kz)\\
\nabla ^2E_1-u_0\varepsilon_0\frac{d^2}{dt^2}E_1 = \frac{d^2}{dz^2}E_1-u_0\varepsilon_0\frac{d^2}{dt^2}E_1 = 0\\易知，E_1是上述方程的一个解'
\\
=>k^2=w^2u_0\epsilon_0\\
E_2 = (x+z)cos(wt+\frac{k|x-z|}{2^{0.5}})\\
\nabla ^2E_2-u_0\varepsilon_0\frac{d^2}{dt^2}E_2 = \frac{d^2}{dz^2}E_2-u_0\varepsilon_0\frac{d^2}{dt^2}E_2≠0\\
E_3 = (x+z)cos(wt+ky)\\
\nabla ^2E_3-u_0\varepsilon_0\frac{d^2}{dt^2}E_3 = u_0\epsilon_0w^2sin(wt+ky)=0\\
综上，E_1,E_3满足\nabla ^2E-u_0\varepsilon_0\frac{d^2}{dt^2}E =0，E_2不满足\\
k^2=w^2u_0\epsilon_0
$$
(b):
$$
D=\epsilon_0E\\
\nabla \times H = \frac{d}{dt}D+J\\
由于J=0,得到：\\
\nabla \times H = \epsilon \frac{d}{dt}E\\
B = \frac{E}{c} = uH\\
H = \frac{E}{c·u_0}\\
H_1 = z\frac{cos(wt-kz)}{c·u_0}\\
H_2 = (x+z)\frac{cos(wt+\frac{k|x-z|}{2^{0.5}})}{c·u_0}\\
H_3 = (x+z)\frac{cos(wt+ky)}{c·u_0}
$$
(c):

$E_1,E_3$属于电磁波，$E_2$违反了$\nabla ·B = 0$

$$
对于E_1,E_2,有：\\
\nabla \times E = -\frac{d}{dt}B\\
\nabla ·B = 0\\
由叉乘的定义可知，B,E的传播方向相互垂直
$$


### Problem 2

(a):

$\lambda = \frac{c}{f}$

- f=60hz, $\lambda = 5000000m$
- f=535-1605khz, $\lambda = 186-560m$
- f=88-108Mhz, $\lambda = 2.7-3.4m$
- f=4-6Ghz, $\lambda = 0.05-0.075m$
- f=~$10^{14}$hz, $\lambda = ~3*10^{-6}m$
- f=~$10^{18}$hz, $\lambda = ~3*10^{-10}m$

(b):

$f=\frac{c}{\lambda}$

- $\lambda = 1000m$, f = $3*10^{5}$
- $\lambda = 1m$, f = $3*10^{8}$
- $\lambda = 0.01m$, f = $3*10^{10}$
- $\lambda = 0.0000001$, f = $3*10^{14}$
- $\lambda = 10^{-10}m$, f = $3*10^{18}$

(c):

$k = \frac{1}{\lambda}K_0$

- $\lambda = 1000m,k = 10^{-3}K_0$
- $\lambda = 1m,k = 1K_0$
- $\lambda = 0.01m,k = 10^{2}K_0$
- $\lambda = 10^{-6}m,k = 10^{6}K_0$
- $\lambda = 10^{-10}m,k = 10^{10}K_0$

### Problem 3

(1):
$$
\nabla \times (\nabla \times E) = \nabla \times 
[\begin{matrix}
x&y&z\\
\frac{d}{dx}&\frac{d}{dy}&\frac{d}{dz}\\
E_x&E_y&E_z
\end{matrix}]
\\
 = [\begin{matrix}
x&y&z\\
\frac{d}{dx}&\frac{d}{dy}&\frac{d}{dz}\\
\frac{d}{dy}E_z-\frac{d}{dz}E_y&\frac{d}{dz}E_x-\frac{d}{dx}E_z&\frac{d}{dy}E_x-\frac{d}{dx}E_y
\end{matrix}]
\\
 = \sum \frac{d}{dy}(\frac{d}{dy}E_x-\frac{d}{dx}E_y)-\frac{d}{dz}(\frac{d}{dz}E_x-\frac{d}{dx}E_z)x\\
 = \nabla(\nabla·E) - \nabla^2E
$$
(2):
$$
\nabla·(E\times H) = \nabla·
[\begin{matrix}
x&y&z\\
E_x&E_y&E_z\\
H_x&H_y&H_z
\end{matrix}]\\
 = \sum \frac{d}{dx}(E_yH_z-E_zH_y)\\
 \sum H_x(\frac{d}{dy}E_z-\frac{d}{dz}E_y)-\sum E_x(\frac{d}{dy}H_z-\frac{d}{dz}H_y)\\
  = H·(\nabla \times E)-E·(\nabla \times H)
$$
(3):
$$
\nabla·(\nabla \times A) = \nabla·
[\begin{matrix}
x&y&z\\
\frac{d}{dx}&\frac{d}{dy}&\frac{d}{dz}\\
A_x&A_y&A_z
\end{matrix}]
 = 0
$$
(4):
$$
\nabla \times(\nabla \phi) = 
[\begin{matrix}
x&y&z\\
\frac{d}{dx}&\frac{d}{dy}&\frac{d}{dz}\\
\frac{d\phi}{dx}&\frac{d\phi}{dy}&\frac{d\phi}{dz}
\end{matrix}]
\\
 = 0
$$

### Problem 4

不能用对z的导数来表示波速，波速应该是有关时间t的导数

k=1时，运行代码得到如下图像：

![image-20220228104932593](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220228104932593.png)

当k=5时，得到如下图像：

![image-20220228105001404](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220228105001404.png)

当k增加时，线的斜率降低，波长减小

### Problem 5

$$
\nabla(A·A) = 2(A·\nabla)A+2A\times (\nabla \times A)\\
证明：\\
2(A·\nabla)A+2A\times(\nabla \times A) = \\
(2\sum \frac{d}{dx}A_x)(A_x+A_y+A_z) + 2A\times 
[\begin{matrix}
x&y&z\\
\frac{d}{dx}&\frac{d}{dy}&\frac{d}{dz}\\
A_x&A_y&A_z
\end{matrix}]
\\
 = (2\sum \frac{d}{dx}A_x)(A_x+A_y+A_z)+2
 [\begin{matrix}
 x&y&z\\
 A_x&A_y&A_z\\
 \frac{d}{dy}Az-\frac{d}{dz}A_y&\frac{d}{dz}A_x-\frac{d}{dx}A_z&\frac{d}{dx}A_y-\frac{d}{dy}A_x
 \end{matrix}]
 \\
  = (2\sum \frac{d}{dx}Ax)(A_x+A_y+A_z) + 2\sum[(\frac{d}{dx}A_y-\frac{d}{dy}A_x)A_y-(\frac{d}{dz}A_x-\frac{d}{dx}A_z)A_z]\\
  = \nabla(A·A)
$$

