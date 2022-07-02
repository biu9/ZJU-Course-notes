from re import X
from turtle import color
import numpy as np 
import matplotlib.pyplot as plt

'''
beta_1 = 1
beta_2 = t-0.5
beta_3 = t^2-t+1/6
beta_4 = t^3-1.5t^2+0.6t-1/20
b_1 = 0.1666667
b_2 = 0.71428
b_3 = 1.694915245
b_4 = 2.777778
画出y = \sum (b_i*beta_i)
'''

b_1 = 0.1666667
b_2 = 0.71428
b_3 = 1.694915245
b_4 = 2.777778
x =  np.linspace(0,1,1000)
y = b_1*1 + b_2*(x-0.5) + b_3*(x**2-x+1/6) + b_4*(x**3-1.5*x**2+0.6*x-1/20)
y_1 = x**5
plt.plot(x,y,color="red")
plt.plot(x,y_1,color="blue")
plt.show()