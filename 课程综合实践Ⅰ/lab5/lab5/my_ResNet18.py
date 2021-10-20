import torch
from torch import nn
import torch.nn.functional as F
from torch.nn.modules.activation import ReLU
from torch.nn.modules.container import Sequential

class ResBlock(nn.Module):
    def __init__(self,inchannel,outchannel,stride=1):
        super(ResBlock, self).__init__()
        #定义残差块中的两个连续卷积层
        self.conv = nn.Sequential(
            #取kernelsize为3，stride为1，padding为1，输出矩阵大小不变
            nn.Conv2d(inchannel,outchannel,kernel_size=3,stride=1,padding=1),
            #对卷积层输出做归一化
            nn.BatchNorm2d(outchannel),
            nn.ReLU(),
            nn.Conv2d(outchannel,outchannel,kernel_size=3,stride=1,padding=1),
            nn.BatchNorm2d(outchannel)
        )
        #定义shortchut
        self.shortcut = nn.Sequential()
        if stride != 1 or inchannel != outchannel:
            self.shortcut = nn.Sequential(
                nn.Conv2d(inchannel,outchannel,kernel_size=1,stride=stride),
                nn.BatchNorm2d(outchannel)
            )

        #前向传播
        def forward(self,x):
            x = self.conv(x)
            #将2个卷积层的输出跟处理过的x相加，实现ResNet的基本结构
            x += self.shortcut(x)
            x = F.relu(x)#nn.relu只能在module中使用
            return x

class basic_block1(nn.Module):
    #定义基础块1，因为输出通道数和输入通道数相同，class参数不取out_channels
    def __init__(self,inchannels):
        super(basic_block1,self).__init__()
        self.conv1 = nn.Sequential(
            nn.Conv2d(inchannels,inchannels,kernel_size=3,stride=1,padding=1),
            nn.ReLU()
        )
        self.conv2 = nn.Conv2d(inchannels,inchannels,kernel_size=3,stride=1,padding=1)
    def forward(self,x):
        y = self.conv1(x)
        y = self.conv2(y)
        return F.relu(x+y)    #输出是输入x+经过两次卷积以后的y的和再relu一下    

class basic_block2(nn.Module):
    def __init__(self,inchannels,outchannels):
        super(basic_block2,self).__init__()
        self.conv1 = nn.Conv2d(inchannels,outchannels,kernel_size=1,stride=2,padding=0)
        self.conv2 = nn.Sequential(
            nn.Conv2d(inchannels,outchannels,kernel_size=3,stride=2,padding=1),
            nn.ReLU(),
            nn.Conv2d(outchannels,outchannels,kernel_size=3,stride=1,padding=1)
        )
        #self.conv3 = nn.Conv2d(inchannels,outchannels,kernel_size=3,stride=1,padding=1)
    def forward(self, x):
        z = self.conv1(x)
        y = self.conv2(x)
        #y = self.conv3(y)
        return F.relu(y+z)

#定义ResNet18
class ResNet18(nn.Module):
    '''output_shape = (image_shape-filter_shape+2*padding)/stride + 1'''
    def __init__(self):
        super(ResNet18, self).__init__()
        self.conv1 = nn.Sequential(
            #输出是3x32x32
            nn.Conv2d(in_channels=3,out_channels=64,kernel_size=7,stride=2,padding=3),
            #得到64x16x16
            nn.ReLU(),
            #经过最大池化后得到64x8x8
            nn.MaxPool2d(kernel_size=3,stride=2,padding=1)
        )
        self.conv2 = basic_block1(inchannels=64)
        self.conv_insert = basic_block1(inchannels=64)
        self.conv3 = basic_block2(inchannels=64,outchannels=128)
        self.conv4 = basic_block1(inchannels=128)
        self.conv5 = basic_block2(inchannels=128,outchannels=256)
        self.conv6 = basic_block1(inchannels=256)
        self.conv7  =basic_block2(inchannels=256,outchannels=512)
        self.conv8 = basic_block1(inchannels=512)
        self.end =  nn.Sequential(
            nn.ReLU()
        )
        self.fc1 = nn.Linear(512,1000)
    def forward(self,x) :
        #print(x.shape)
        #输入图片的尺寸是[3, 32, 32]
        x = self.conv1(x)
        #print(x.shape)
        x = self.conv2(x)
        #print(x.shape)
        x = self.conv_insert(x)
        #print(x.shape)
        x = self.conv3(x)
        #print(x.shape)
        x = self.conv4(x)
        #print(x.shape)
        x = self.conv5(x)
        #print(x.shape)
        x = self.conv6(x)
        #print(x.shape)
        x = self.conv7(x)
        #print(x.shape)
        x = self.conv8(x)
        #print(x.shape)
        x = self.end(x)
        #print(x.shape)
        x = x.view(x.size(0), -1) #转化为二维张量
        #print(x.shape)
        x = self.fc1(x)
        return x


