import numpy as np
import matplotlib.pyplot as plt
from sympy import *
import math

def myIntegrate(t):
    sum = 0
    for j in np.arange(-1000,0,0.1):
        if(j == 0):
            y = 0.25
        else:
            y = (2/math.pi)*(math.sin(j*0.5)**2/(j*math.sin(j)))*math.cos(j*t)
        sum += y*0.1
    return sum

def approximate():
    x = np.arange(-10,10,0.1)
    y = []
    for i in np.arange(-10,10,0.1):
        y.append(myIntegrate(i))
    return x,y

def convTest():
    y = []
    for i in np.arange(-10,10,0.1):
        sum = 0
        for j in np.arange(0,2,0.1):
            sum += myIntegrate(i-j)*0.1
        y.append(sum)
    return y

def main():
    x,y = approximate()
    xTest = np.arange(-10,10,0.1)
    yTest = convTest()
    fig = plt.figure()
    ax1 = fig.add_subplot(211)
    ax2  = fig.add_subplot(212)
    ax1.plot(x,y)
    ax2.plot(xTest,yTest)
    plt.show()

main()

