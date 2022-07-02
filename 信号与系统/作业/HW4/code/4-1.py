from random import randrange
import numpy as np

'''
h = [2,0,1,1,1,2]
x = [3,2,1]
y = h * x = 
[2,0,1,1,1,2] 
* 
[[3,2,1,0,0,0,0,0],
[0,3,2,1,0,0,0,0],
[0,0,3,2,1,0,0,0],
[0,0,0,3,2,1,0,0],
[0,0,0,0,3,2,1,0],
[0,0,0,0,0,3,2,1]]
= [6 4 5 5 6 9 5 2]
1x6 * 6x8 = 1x8
h = x^-1 * y
'''
def calculateInpuseResponse(x,y):
    h = np.zeros(len(y) - len(x) + 1)
    xMatrix = np.zeros((len(h),len(y)))
    for i in range(len(h)):
        xMatrix[i,i:i+len(x)] = x
    
    xMatrix1 = np.zeros((len(h),len(h)))
    for i in range(len(h)):
        for j in range(len(h)):
            xMatrix1[i][j] = xMatrix[i][j]

    y1 = np.zeros(len(h))
    for i in range(len(h)):
        y1[i] = y[i]
    try:
        xInv = np.linalg.inv(xMatrix1)
    except:
        print("No sequence satisfies this condition")
    #xInv * y1
    for i in range(len(h)):
        for j in range(len(h)):
            h[i] += xInv[j][i] * y1[j]
    return h

def main():
    h = np.array([2,0,1,3,1,2,3])
    x = np.array([3,2,1,3])
    y = np.convolve(x,h)
    res = calculateInpuseResponse(x,y)
    print("h:",res)

main()