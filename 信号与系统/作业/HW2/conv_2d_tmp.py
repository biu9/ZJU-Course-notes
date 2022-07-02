from pprint import pprint
from cv2 import imshow
import numpy as np
from rsa import sign
from scipy import signal
from fractions import Fraction

import matplotlib.pyplot as plt
import pylab
import cv2
import matplotlib.colors as mat_color

import io
import sys

from torch import float32
sys.stdout = io.TextIOWrapper(sys.stdout.buffer,encoding='utf-8')

def myCond2d(matrixDem,convDem,x,y):
    #卷积加0
    insertZero = np.zeros(matrixDem)
    inserZeroRow = np.transpose(np.zeros(matrixDem+2))

    xTmp = np.insert(x,0,insertZero,axis=0)
    xTmp = np.insert(xTmp,matrixDem+1,insertZero,axis=0)
    xTmp = np.insert(xTmp,0,inserZeroRow,axis=1)
    xTmp = np.insert(xTmp,matrixDem+1,inserZeroRow,axis=1)
    convResDem = matrixDem-convDem+3
    convRes = np.zeros((convResDem,convResDem))

    for i in range (0,convResDem):
        for j in range (0,convResDem):
            for convX in range(0,convDem):
                for convY in range(0,convDem):
                    convRes[i][j] += xTmp[i+convX][j+convY]*y[convX][convY]
    #print(convRes)
    return convRes

#检查输出
x = np.array([
    [1,2,3,4,5],
    [6,7,8,9,10],
    [11,12,13,14,15],
    [16,17,18,19,20],
    [21,22,23,24,25]
])

y = np.array([
    [1,2,1],
    [0,0,0],
    [-1,-2,-1]
])
matrixDem = 5
convDem = 3

#自带的二维卷积
conv2d = signal.convolve2d(x,y,mode='same')
print("自带卷积的结果： ",conv2d)

#自己写的二维卷积
res = myCond2d(matrixDem,convDem,x,y)
print("自己写的卷积的结果： ",res)

#对图片进行卷积
kernel1 = np.array([
    [1/9,1/9,1/9],
    [1/9,1/9,1/9],
    [1/9,1/9,1/9]
])
kernel2 = np.array([
    [-1/9,-1/9,-1/9],
    [-1/9,8/9,-1/9],
    [-1/9,-1/9,-1/9]
])

#读取图片并归一化
img = cv2.imread('./lenna.jpg')
res = np.zeros(img.shape,dtype=np.float32)
res = img / 255
img = np.uint8(res*255)
#print("img: ",img)


#opencv的卷积
img1 = cv2.filter2D(img,-1,kernel=kernel1)
img2 = cv2.filter2D(img,-1,kernel=kernel2)
cv2.imwrite('kernel1.jpg',img1)
cv2.imwrite('kernel2.jpg',img2)

#自己写的卷积
myImg1 = np.zeros((512,512,3),dtype=np.float32)
for i in range(0,3,1):
    myImg1[:,:,i] = myCond2d(512,3,img[:,:,i],kernel1)
cv2.imwrite('myImg1.jpg',myImg1)

myImg2 = np.zeros((512,512,3),dtype=np.float32)
for i in range(0,3,1):
    myImg2[:,:,i] = myCond2d(512,3,img[:,:,i],kernel2)
cv2.imwrite('myImg2.jpg',myImg2)



