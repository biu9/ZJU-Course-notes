# Lec07

### 拉格朗日插值多项式

$$
L_k=\prod_{i≠k}^n\frac{x-x_i}{x_k-x_i}\\
P(x) = \sum_{i=0}^nL_if(x_i)
$$

### 内维尔迭代

$$
Q_{i,j} = \frac{(x-x_{i-j})Q_{i,j-1}-(x-x_i)Q_{i-1,j-1}}{x_i-x_{i-j}}\\
Q_{i,j} = P_{i-j,i-j+1,...,i-1,i}\\
e.g:\\
P_{0,1} = \frac{(x-x_0)P_1-(x-x_1P_0)}{x_1-x_0}\\
P_{1,2} = \frac{(x-x_1)P_2-(x-x_2)P_1}{x_2-x_1}\\
P_{0,1,2} = \frac{(x-x_0)P_{1,2}-(x-x_2)P_{0,1}}{x_2-x_0}
$$

