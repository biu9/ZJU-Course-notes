# Lec05

### 收敛矩阵

当k趋向于∞时，如果A矩阵满足：$lim(A^k)_{ij} = 0$则称A收敛

以下条件等价：

### 矩阵范数

- A矩阵的无穷范数是一行中所有元素绝对值和最大的值

<img src="C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220109163505234.png" alt="image-20220109163505234"  />

- A矩阵的二阶范数是$AA^T$矩阵谱半径开根号

### 谱半径

> 一个矩阵所有特征值的最大值

可以通过$det(A-\lambda I)=0$来计算特征值$\lambda$

### 雅可比迭代

> 把待求的AX=b矩阵写成BX=0的形式，再在第i行中提取出$x_i$到等式的一边，然后把初始的x向量带进去进行迭代

<img src="C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220109172805171.png" alt="image-20220109172805171"  />

### 高斯-赛德尔迭代

> 基本思路与雅可比迭代类似，但迭代过程中的$x_i^{(k)}$是动态变化的，也就是说$x_4^{(3)}可以由x_3^{(4)}迭代得到$

<img src="C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220109173225006.png" alt="image-20220109173225006"  />

![image-20220109173554932](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20220109173554932.png)

