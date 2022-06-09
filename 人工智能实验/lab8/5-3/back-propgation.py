import numpy as np
import matplotlib.pyplot as plt

#输入三维向量
D_in = 3
#输出一维向量
D_out = 1
#隐藏层神经元个数
H = 4

w1 = np.random.rand(H, D_in) # 隐藏层
w2 = np.random.randn(D_out, H) # 输出层

#创建训练数据
x = np.array([
    [0,0,1,1],
    [0,1,0,1],
    [1,1,1,1]
])
y = np.array([
    [0,1,1,0]
])

#learning rate
lr = 1e-2

for i in range(5000):
    #前向传播
    h1 = w1.dot(x)  #输入数据传入隐藏层
    h_sigmoid = 1 / (1 + np.exp(-h1))   #sigmoid激活函数
    
    y_pred = w2.dot(h_sigmoid)  #隐藏层传入输出层

    #计算损失函数
    loss = np.square(y_pred - y).sum()
    print("back propgation epoch %d, loss: %f" % (i, loss))
    plt.plot(i, loss, 'ro')

    #反向传播
    grad_y_pred = 2.0 * (y_pred - y)
    grad_w2 = grad_y_pred.dot(h1.T) #计算loss对于w2的梯度，对应于2q*x^T

    grad_sigmod = w2.T.dot(grad_y_pred)

    grad_h = grad_sigmod * h_sigmoid * (1 - h_sigmoid)

    # 最后计算Loss对隐藏层w1的偏导数，上游梯度为grad_h，，local gradient为x，对应于公式的2qx^T
    grad_w1 = grad_h.dot(x.T) 

    #更新权重
    w1 -= lr * grad_w1
    w2 -= lr * grad_w2

plt.title('bp-loss')
plt.show()
#输出训练后的结果
print(y_pred)

