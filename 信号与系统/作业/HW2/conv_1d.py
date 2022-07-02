from pprint import pprint
import numpy as np
import time

import io
import sys

from numpy.lib.function_base import average
sys.stdout = io.TextIOWrapper(sys.stdout.buffer,encoding='utf-8')

x = np.random.random(10000)
y = np.random.random(10000)


#调用numpy中的卷积函数
timeBegin = time.time()
res = np.convolve(x, y, mode='full')
timeEnd = time.time()
print("numpy time:", timeEnd - timeBegin)

#自己写的卷积函数
myConv = np.array([])

timeBegin = time.time()
for i in range(len(x)+len(y)-1):
    tmp = 0
    for j in range(len(x)+len(y)-1):
        if(i-j>=0 and i-j<len(x) and i-j<len(y) and j < len(y) and j < len(x)):
            tmp += round(x[j]*y[i-j],100)
    if(tmp != 0):
        myConv = np.append(myConv, tmp)
timeEnd = time.time()
print("my time:", timeEnd - timeBegin)

#判断两个结果是否一样
#for i in range(len(res)):
    #print("第",i,"个元素,numpy的结果是  ",res[i],",自己写的结果是   ",myConv[i],",是否一样：    ",res[i]==myConv[i])
