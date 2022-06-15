# Steepest Descent

### method

- evaluating g at an initial approximation $x^{(0)}=(x_1^{(0)},x_2^{(0)}...x_n^{(0)})^t$

- determine a direction from $x^{(0)}$ that results in a decrease in the value $x^{(1)}$

- move an appropriate amount in this direction and call the new value $x^{(1)}$

- repeat step 1 through 3 with replaced x

  $x^{(k)}=x^{(k-1)}-\alpha \nabla g(x^{(0)})$

### the gradient of a function

​	for a function g, the gradient of g at $x = (x_1,x_2...x_n)^t$ is denoted $\nabla g(x)$, and defined by:
$$
\nabla g(x)=(\frac{\partial g}{\partial x_1}(x),\frac{\partial g}{\partial x_2}(x)...\frac{\partial g}{\partial x_n}(x))^t\\
=>\nabla g(x)=2J(x)^tF(x)
$$

### determine $\alpha$

​	to determine an appropriate choice for $\alpha$, consider the single-variable function:
$$
h(\alpha)=g(x^{(0)}-\alpha \nabla g(x^{(0)}))
$$
the value of $\alpha$ that minimizes h is the value we need
