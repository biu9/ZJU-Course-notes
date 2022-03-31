import numpy as np
from sympy import *
import matplotlib.pyplot as plt

import io
import sys

from numpy.lib.function_base import average
sys.stdout = io.TextIOWrapper(sys.stdout.buffer,encoding='utf-8')

x = 2*np.random.rand(100,1)
y = 4+3*x+np.random.randn(100,1)

tmp = np.ones(100)
xTmp = np.insert(x,0,tmp,axis=1)

#对x，y进行线性回归
X = np.matrix(xTmp)
res = ((X.I))*y
print("结果矩阵为:",res)
print("常数项为:",float(res[0]))
print("系数为:",float(res[1]))
print("x=0时的预测结果为:",float(res[0])+0*float(res[1]))
print("x=2时的预测结果为:",float(res[0])+2*float(res[1]))

#画图
plt.scatter(x,y)
plt.scatter(0,float(res[0])+0*float(res[1]))
plt.text(0,float(res[0])+0*float(res[1]),"result when x=0")
plt.scatter(2,float(res[0])+2*float(res[1]))
plt.text(2,float(res[0])+2*float(res[1]),"result when x=2")
plt.show()