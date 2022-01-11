# Lec12

### 欧拉方法解微分方程

定义h为步长，$h = \frac{x_n-x_0}{n}，t_i = x_0+(i-1)h，w(0) = f(x_0)$
$$
w_{i+1} = w_i+hf(t_i,w_i)
$$

### 高阶泰勒方法解微分方程

$$
w_{i+1} = w_i+hT^{(n)}(t_i,w_i)\\
T^{(n)}(t_i,w_i) = f(t_i,w_i)+...\frac{h^{n-1}}{n!}f^{(n-1)}(t_i,w_i)
$$

### Runge-Kutta 方法

$$
w_{i+1} = w_i+hf(t_i+\frac{h}{2},w_i+\frac{h}{2}f(t_i,w_i))
$$

