from cProfile import label
import math
from turtle import color
import numpy as np
import matplotlib.pyplot as plt


fig = plt.figure()
n = np.array([1000])
x = np.arange(-10,10,0.01)
for i in n:
    y = []
    for j in np.arange(-10,10,0.01):
        res = 0.5
        for k in np.arange(1,i+1,1):
            tmp = (2*math.sin(k*math.pi/2))/(k*math.pi)*(math.cos(k*math.pi/2*j))
            res += tmp
        y.append(res)
    plt.plot(x,y)
plt.show()