from cmath import isnan
from turtle import color
import numpy as np
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt

#load data
data = np.loadtxt('4.2/secom.txt',delimiter=' ')
#print(data)

#处理缺失值
for i in range(data.shape[1]):
    tempCol = data[:,i]
    nanNum = np.count_nonzero(np.isnan(tempCol))
    if(nanNum != 0):
        tempCol[np.isnan(tempCol)] = np.mean(tempCol[~np.isnan(tempCol)])
    data[:,i] = tempCol

#fit model
model = PCA(n_components=3)
newRes = model.fit_transform(data)
invRes = model.inverse_transform(newRes)

res = 0
flag = 0
for i in range(data.shape[1]):
    tmpModel = PCA(n_components=i+1)
    tmpRes = tmpModel.fit_transform(data)
    y = np.sum(tmpModel.explained_variance_ratio_)
    plt.plot(i+1,y,color="red")
    if(y > 0.91 and flag == 0):
        res = i+1
        flag = 1
    
plt.show()
print(res)