import numpy as np
from numpy.linalg import *

import io
import sys
sys.stdout = io.TextIOWrapper(sys.stdout.buffer,encoding='utf-8')

#使用三次最小二乘拟合以下数据
#y: 1 43 75 155 196 219 271 318 351 385 425 466 503 537 575 599 626
#x: 1761 1767 1771 1772 1774 1775 1777 1779 1780 1782 1783 1785 1786 1788 1789 1791 1791

y = np.array([1, 43, 75, 155, 196, 219, 271, 318, 351, 385, 425, 466, 503, 537, 575, 599, 626],dtype='int64')
x = np.array([1761,1767,1771,1772,1774,1775,1777,1779,1780,1783,1785,1786,1788,1789,1791,1791],dtype='int64')
m = 17

sumXi=sumYi=0       #x，y的和
sumXi2=sumYi2=0     #x^2,y^2的和
sumXiYi=0           #x*y的和
sumXi3=0            #x^3的和
sumXi4=0            #x^4的和
sumXi5=0            #x^5的和
sumXi6=0            #x^6的和
sumXi2Yi=0          #x^2*y的和
sumXi3Yi=0          #x^3*y的和

for i in range(0,16):
    sumXi += x[i]
    sumYi += y[i]
    sumXi2 += x[i]*x[i]
    sumYi2 += y[i]*y[i]
    sumXiYi += x[i]*y[i]
    sumXi3 += x[i]*x[i]*x[i]
    sumXi4 += x[i]*x[i]*x[i]*x[i]
    sumXi5 += x[i]*x[i]*x[i]*x[i]*x[i]
    sumXi6 += pow(float(x[i]),6)
    sumXi2Yi += x[i]*x[i]*y[i]
    sumXi3Yi += x[i]*x[i]*x[i]*y[i]

A = np.array([
    [m,sumXi,sumXi2,sumXi3],
    [sumXi,sumXi2,sumXi3,sumXi4],
    [sumXi2,sumXi3,sumXi4,sumXi5],
    [sumXi3,sumXi4,sumXi5,sumXi6]
])
B = np.array([
    [sumYi],
    [sumXiYi],
    [sumXi2Yi],
    [sumXi3Yi]
])
res = solve(A,B)
a0 = float(res[0])
a1 = float(res[1])
a2 = float(res[2])
a3 = float(res[3])
print("a0 = ",a0)
print("a1 = ",a1)
print("a2 = ",a2)
print("a3 = ",a3)
#预测y=173时的x
p=np.array([a3,a2,a1,a0-173])
print(np.roots(p))
print("y=173时的x =",np.roots(p)[0])
#预测y=726时的x
p=np.array([a3,a2,a1,a0-726])
print(np.roots(p))
print("y=726时的x =",np.roots(p)[0])