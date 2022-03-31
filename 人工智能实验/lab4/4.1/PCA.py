from numpy import *
import matplotlib.pyplot as plt
 
def pca(dataMat, topNfeat = 999999):
    meanValues = mean(dataMat,axis=0) # 竖着求平均值，数据格式是m×n
    meanRemoved = dataMat - meanValues  # 0均值化  m×n维
    covMat = cov(meanRemoved,rowvar=0)  # 每一列作为一个独立变量求协方差  n×n维
    eigVals, eigVects = linalg.eig(mat(covMat)) # 求特征值和特征向量  eigVects是n×n维
    eigValInd = argsort(-eigVals)  # 特征值由大到小排序，eigValInd十个arrary数组 1×n维
    eigValInd = eigValInd[:topNfeat]  # 选取前topNfeat个特征值的序号  1×r维
    redEigVects = eigVects[:,eigValInd] # 把符合条件的几列特征筛选出来组成P  n×r维
    lowDDataMat = meanRemoved * redEigVects  # 矩阵点乘筛选的特征向量矩阵  m×r维 公式Y=X*P
    reconMat = (lowDDataMat * redEigVects.T) + meanValues  # 转换新空间的数据  m×n维
    return lowDDataMat, reconMat
 
def drawPoints(dataset1,dataset2):  # 画图，dataset1是没降维的数据，dataset2是数据映射到新空间的数据
    fig = plt.figure()
    ax1 = fig.add_subplot(211)
    ax2 = fig.add_subplot(212)
    ax1.scatter(dataset1[:,0],dataset1[:,1],marker='s',s=40,color='red')
    dataset2 = array(dataset2)
    ax2.scatter(dataset2[:,0],dataset2[:,1],s=40,color='blue')
 
    plt.show()
 
if __name__ == '__main__':
    data = loadtxt('4.1/testSet.txt',delimiter='	')
    proccess_data, reconMat = pca(data,1)
    drawPoints(data,reconMat)