from torch import nn
import torch
import matplotlib.pyplot as plt
import torch.nn.functional as F

D_in, H, D_out = 3, 4, 1

#创建训练数据
x = torch.Tensor([
    [0,0,1],
    [0,1,1],
    [1,0,1],
    [1,1,1]
])
y = torch.Tensor([
    [0],
    [1],
    [1],
    [0]
])

model = torch.nn.Sequential(
    torch.nn.Linear(D_in,H),    
    nn.ReLU(),
    torch.nn.Linear(H, D_out),
)

lr = 1e-2

loss_fn = torch.nn.MSELoss(reduction='sum')

# 梯度下降策略
optimizer = torch.optim.SGD(model.parameters(),lr=lr,momentum=0.01)
for it in range(5000):
    y_pred = model(x) #model.forward()
    
    loss = loss_fn(y_pred,y)
    if(loss < 1e-8):
        break
    print("\r epoch={} loss={}".format(it,loss), end=' ')
    
    optimizer.zero_grad()
    loss.backward()
    
    optimizer.step()

    plt.plot(it,loss.item(),'ro')

print("")
print(model(x))
plt.show()