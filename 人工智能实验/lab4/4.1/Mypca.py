import numpy as np
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt

#load data
data = np.loadtxt('4.1/testSet.txt',delimiter='	')

#fit model
model = PCA(n_components=2)
newRes = model.fit_transform(data)
invRes = model.inverse_transform(newRes)
print(invRes)

#draw
fig = plt.figure()
ax1 = fig.add_subplot(211)
ax2 = fig.add_subplot(212)
ax1.scatter(data[:,0],data[:,1],marker='s',s=40,color='red')
ax2 = plt.scatter(invRes[:,0],invRes[:,1],marker='s',s=40,color='blue')
plt.show()