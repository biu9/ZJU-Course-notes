# Lec11

### 梯形法则(trapezoidal rule)

> 就是用首尾两点以及x轴组成一个梯形来近似积分

$$
\int_a^b f(x)dx= \frac{(f(a)+f(b))(b-a)}{2}-\frac{(b-a)^3}{12}f''(\xi)
$$

### Simpson's rule

$$
\int_{x_0}^{x_2}f(x)dx = \frac{h}{3}[f(x_0)+4f(x_1)+f(x_2)]-\frac{h^5}{90}f^{(4)}(\xi)\\
h = \frac{x_2-x_0}{2}
$$

