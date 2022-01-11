# Lec01-note

### round-off error(舍入误差)

> the error that is produced when a calculator or computer is used to performed real number calculations is called **round-off error**

取数的**k-digits十进制表示**:	$y=0.d_1d_2...d_k*10^n$

**chopping(截断)**，指的是去掉k位数字之后的数字以产生k-digits的十进制表示，$\pi$的5-digits的十进制表示就是0.314159265x10去掉第五位之后的数字得到0.31415x10，也就是3.1415

**rounding(舍入)**，指的是加上$5*10^{n-(k+1)}$以后再对数字进行截断以得到k-digits的十进制表示，$\pi$的5-digits的十进制表示使用rounding时则对0.31415加上0.00001以后再乘以10得到3.1416

### errors and significant digits

如果p'是p的逼近，**absolute error(绝对误差)**是|p-p'|,**relative error**,是$\frac{|p-p'|}{p}$

### rate of convergence

$$
假设\beta是一个收敛于0的序列，\alpha收敛于a,如果\\
存在一个常数K使得：\\
|\alpha_n-\alpha|<=K|\beta_n|\\
我们定义\alpha以O(\beta_n)的收敛速度收敛到a\\
也可以表示为：\alpha_n = \alpha+O(\beta_n)
$$

