from cProfile import label
from tokenize import group
from numpy import *
import operator
import numpy as np

def creatDataSet():
    group = np.loadtxt('train.txt',usecols=(0,1,2))
    labels = np.loadtxt('train.txt',usecols=(3))
    #group = array([[1.0, 1.1], [1.0, 1.0], [0, 0], [0, 0.1]])
    #labels = ['A','A','B','B']
    return group,labels

def classify0(inX,dataSet,labels,k):
    # shape读取数据矩阵第一维度的长度
    dataSetSize = dataSet.shape[0]
    # tile重复数组inX，有dataSet行 1个dataSet列，减法计算差值
    diffMat = tile(inX,(dataSetSize,1)) - dataSet
    # **是幂运算的意思，这里用的欧式距离
    sqDiffMat = diffMat ** 2
    # 普通sum默认参数为axis=0为普通相加，axis=1为一行的行向量相加
    sqDistances = sqDiffMat.sum(axis=1)
    distances = sqDistances ** 0.5
    # argsort返回数值从小到大的索引值（数组索引0,1,2,3）
    sortedDistIndicies = distances.argsort()
    # 选择距离最小的k个点
    classCount = {}
    for i in range(k):
        # 根据排序结果的索引值返回靠近的前k个标签
        voteLabel = labels[sortedDistIndicies[i]]
        # 各个标签出现频率
        classCount[voteLabel] = classCount.get(voteLabel,0) +1
    ##!!!!!  classCount.iteritems()修改为classCount.items()
    #sorted(iterable, cmp=None, key=None, reverse=False) --> new sorted list。
    # reverse默认升序 key关键字排序itemgetter（1）按照第一维度排序(0,1,2,3)
    sortedClassCount = sorted(classCount.items(),
                              key=operator.itemgetter(1),reverse=True)
    return sortedClassCount[0][0]
