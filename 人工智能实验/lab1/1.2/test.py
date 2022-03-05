import KNN
import numpy as np

group,labels = KNN.creatDataSet()
print("group:",group)
print("labels:",labels)
print("testData:",np.loadtxt("test.txt",usecols=(0,1,2)))
testData = np.loadtxt("test.txt",usecols=(0,1,2)).reshape(100,-1)
trueData = np.loadtxt("test.txt",usecols=(3))
print("testData:",testData[0])
trueNum = 0
for i in range(100):
    print("the [",i,"] data,","predict result:",KNN.classify0(testData[i],group,labels,3),"true result:",trueData[i])
    if(KNN.classify0(testData[i],group,labels,3) == trueData[i]):
        trueNum += 1
print("trueNum:",trueNum)
print("truethRate:",trueNum/100)