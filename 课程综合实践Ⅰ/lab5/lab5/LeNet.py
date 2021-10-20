import torch
from torch import nn
import torch.nn.functional as F

class LeNet(nn.Module):
    def __init__(self):
        super(LeNet,self).__init__()
        #卷积层与池化层
        self.conv1 = nn.Sequential(
            #卷积层，输入通道数为1，输出通道数为6，卷积核大小为7x7，步长为1，填充三层
            nn.Conv2d(1,7,kernel_size=7,stride=1,padding=3),#输出仍为nxn大小的矩阵
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2,stride=2,padding=0)
        )
        self.conv2 = nn.Sequential(
            nn.Conv2d(7,16,kernel_size=5,stride=1,padding=0),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2,stride=2,padding=0)
        )

        #全连接层
        self.fc1 = nn.Sequential(
            nn.Linear(16*5*5,120),
            nn.ReLU()
        )
        self.fc2 = nn.Sequential(
            nn.Linear(120,84),
            nn.ReLU()
        )
        self.fc3 = nn.Linear(84,19)
    def forward(self,x):
        x = self.conv1(x)
        x = self.conv2(x)

        x = x.view(x.size(0), -1) #转化为二维张量
        x = self.fc1(x)
        x = self.fc2(x)
        x = self.fc3(x)
        return x

