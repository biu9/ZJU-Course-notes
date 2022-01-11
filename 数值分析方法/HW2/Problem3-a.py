from functools import singledispatch
import numpy as np
import math
from numpy.linalg import *
X=np.array([
    [3,0.5*(-1/6)*math.pi*math.sin(0.5*(-1/6)*math.pi),0.5*math.sin(0.5*(-1/6)*math.pi)],
    [4,-1250*0.5+2,0],
    [-0.5*math.pow(math.e,-0.25),-0.5*math.pow(math.e,-0.25),20]
])
F=np.array([
    [1-math.cos(0.5*(-1/6)*math.pi)],
    [-621/4],
    [math.pow(math.e,-0.25)-1]
])
print(X)
print(F)
Y=solve(X,F)
Y = Y+np.array([
    [0.5],
    [0.5],
    [-1*math.pi/6]
])
print(Y)