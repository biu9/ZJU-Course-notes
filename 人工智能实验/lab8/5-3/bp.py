import numpy as np

# numpy构建神经网络
# N为训练数据个数，D_in为输入层大小，H为隐藏层大小，D_out为输出层大小
# 我们定义一个输入层为1000维向量，隐藏层为100个神经元，输出层层10个神经元的神经网络
batch_size, D_in, H, D_out =64, 1000, 100, 10

# 随机创建训练数据
x = np.random.randn(D_in, batch_size)
y = np.random.randn(D_out, batch_size)

# 根据我们的模型，包含2个权重层，分别为100个神经元的隐藏层和10个神经元的输出层
w1 = np.random.randn(H, D_in) # 隐藏层
w2 = np.random.randn(D_out, H) # 输出层

lr = 1e-4
for t in range(3000):
    # 进行前向传播
    h = w1.dot(x) # 输出数据传入隐藏层
    h_sigmod = 1 / (1 + np.exp(-h))
    y_pred = w2.dot(h_sigmod) # 隐藏层输出的数据进入输出层
    
    # 计算损失函数
    loss = np.square(y_pred - y).sum()
    print("\r epoch={} loss={}".format(t, loss), end=' ')
    
    # 反向传播
    grad_y_pred = 2.0 * (y_pred - y) # 首先Loss对输出数据求导，这个结果将是输出层的上游梯度,对应于公式的 2q
    
    grad_w2 = grad_y_pred.dot(h.T) # 这里计算Loss对输出层w2的偏导数，上游梯度为grad_y_pred，local gradient为h，对应于公式的2qx^T
    
    # 为了计计算Loss对w1的偏导数，W1*x中的本地偏导数很容易得到是X^T，但是还需要求得上一层传播过来的上游偏导数
    grad_sigmod = w2.T.dot(grad_y_pred) # 
    
    # 
    grad_h = grad_sigmod*(h_sigmod*(1-h_sigmod))
    
    grad_w1 = grad_h.dot(x.T) # 最后计算Loss对隐藏层w1的偏导数，上游梯度为grad_h，，local gradient为x，对应于公式的2qx^T
    
    # 执行梯度下降
    w1 -= lr * grad_w1
    w2 -= lr * grad_w2