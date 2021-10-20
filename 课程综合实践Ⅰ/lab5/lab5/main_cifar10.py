from my_ResNet18 import *
import  torch
from    torch.utils.data import DataLoader
from    torchvision import datasets
from    torchvision import transforms
from    torch import nn, optim
import torchvision
import numpy as np
import matplotlib.pyplot as plt
from torch.utils.tensorboard import SummaryWriter   
#import io
#import sys
#sys.stdout = io.TextIOWrapper(sys.stdout.buffer,encoding='utf-8')

#load data
transform = torchvision.transforms.ToTensor()   #定义数据预处理方式：转换 PIL.Image 成 torch.FloatTensor
 
train_data = torchvision.datasets.CIFAR10(root="data",    #数据目录，这里目录结构要注意。
                                        train=True,                                     #是否为训练集
                                        transform=transform,                            #加载数据预处理
                                        download=False)                                 #是否下载
test_data = torchvision.datasets.CIFAR10(root="data",
                                        train=False,
                                        transform=transform,
                                        download=False)

#数据加载器:组合数据集和采样器 
train_loader = torch.utils.data.DataLoader(dataset = train_data,batch_size = 128,shuffle = True) 
test_loader = torch.utils.data.DataLoader(dataset = test_data,batch_size = 64,shuffle = False)


#define loss
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")   #若检测到GPU环境则使用GPU，否则使用CPU
net = ResNet18().to(device)    #实例化网络，有GPU则将网络放入GPU加速
loss_fuc = nn.CrossEntropyLoss()    #多分类问题，选择交叉熵损失函数
optimizer = optim.SGD(net.parameters(),lr = 0.01,momentum = 0.9)   #选择SGD，学习率取0.01

writer = SummaryWriter('log')

#开始训练
EPOCH = 1   #迭代次数
for epoch in range(EPOCH):
    sum_loss = 0
    #数据读取
    for i,data in enumerate(train_loader):
        inputs,labels = data
        inputs, labels = inputs.to(device), labels.to(device)   #有GPU则将数据置入GPU加速
 
        # 梯度清零
        optimizer.zero_grad()
 
        # 传递损失 + 更新参数
        output = net(inputs)
        loss = loss_fuc(output,labels)
        loss.backward()
        optimizer.step()

        writer.add_scalar('loss', loss.item(), i+epoch*781)

    correct = 0
    total = 0
 
    for data in test_loader:
        test_inputs, labels = data
        test_inputs, labels = test_inputs.to(device), labels.to(device)
        outputs_test = net(test_inputs)
        _, predicted = torch.max(outputs_test.data, 1)  #输出得分最高的类
        total += labels.size(0) #统计50个batch 图片的总个数
        correct += (predicted == labels).sum()  #统计50个batch 正确分类的个数

    writer.add_scalar('truth rate', 100*correct.item()/total, epoch)
