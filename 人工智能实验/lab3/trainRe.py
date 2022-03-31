from cProfile import label
from gettext import find
from statistics import mode
import sys
import os
import pickle
from nbformat import read
import numpy as np
from pandas import array
import scipy.io as sio
import matplotlib
import matplotlib.pyplot as plt
from sklearn import svm
import pickle

from sklearn.preprocessing import scale
from sympy import false

#load the data and labels
def loadData():
    trainData = np.loadtxt('./data/training.txt', delimiter=' ',usecols=(0,1,2,3,4,5),dtype=float)
    trainLabels = np.loadtxt('./data/training.txt', delimiter=' ',usecols=(6),dtype=float)
    testData = np.loadtxt('./data/test.txt', delimiter=' ',usecols=(0,1,2,3,4,5),dtype=float)
    testLabels = np.loadtxt('./data/test.txt', delimiter=' ',usecols=(6),dtype=float)
    return trainData,trainLabels,testData,testLabels

def trainModel(trainData,trainLabels,testData,testLabels,gamm,C,kernel):
    #调用svm模型,自定义gamma、C、kernel等参数
    clf = svm.SVC(kernel=kernel,C=C,gamma=gamm,shrinking=0)
    clf.fit(trainData,trainLabels)
    #save model
    with open('./model/'+str(kernel)+'_'+str(gamm)+'_'+str(C)+'.pkl','wb') as f:
        pickle.dump(clf,f)
    return clf.score(testData,testLabels)

def findBestModel(trainData,trainLabels,testData,testLabels,gammScle,cScale,kernel):
    res=0.5
    bestGammaIndex = 0;
    bestCIndex = 0;
    #遍历gamma和C；寻找最优参数
    for i in range(len(gammScle)):
        for j in range(len(cScale)):
            gamm = 2**gammScle[i]
            C = 2**cScale[j]
            score = trainModel(trainData=trainData,
                    trainLabels=trainLabels,testData=testData,
                    testLabels=testLabels,gamm=gamm,C=C,kernel=kernel)
            #记录结果
            with open('./result.txt','a') as f:
                f.write("kernel: "+str(kernel)+"     |gamm:    "+str(gamm)+"   |C:   "+str(C)+"      |score: "+str(score)+'\n')
            if(abs(0.5-score)>abs(0.5-res)):
                res = score
                bestGammaIndex = i
                bestCIndex = j
    #返回较优参数，之后进行下一步寻找以找到最优参数
    return bestCIndex,bestGammaIndex

#细化训练
def trainDeeper(trainData,trainLabels,testData,testLabels,gammaIndex,cIndex,kernel,gammaScle,cScale):
    res = 0.5
    bestGamma = 0
    bestC = 0
    #把gamma和C细化
    gammaleft = 2**gammaScle[gammaIndex]
    Cleft = 2**cScale[cIndex]
    gammaright = 2**gammaScle[gammaIndex+1]
    Cright = 2**cScale[cIndex+1]
    #设置左右细化的步长
    step = 10
    for i in range(gammaleft,gammaright,step):
        for j in range(Cleft,Cright,step):
            score = trainModel(trainData=trainData,trainLabels=trainLabels,
                    testData=testData,testLabels=testLabels,
                    gamm=i,C=j,kernel=kernel)
            if(abs(0.5-score)>abs(0.5-res)):
                res = score
                bestGamma = i
                bestC = j
    return bestC,bestGamma

def main():
    trainData,trainLabels,testData,testLabels = loadData()
    kernel = ['rbf','linear','poly','sigmoid']
    gammaScale = [-3,-1,1,3,5]
    Cscale = [-3,-1,1,3,5]
    for i in kernel:
        #训练模型
        bestGammaIndex,bestCIndex = findBestModel(trainData=trainData,trainLabels=trainLabels,
                testData=testData,testLabels=testLabels,kernel=i,
                gammScle=gammaScale,cScale=Cscale)
        #细化训练
        bestC,bestGamma = trainDeeper(trainData=trainData,trainLabels=trainLabels,
                gammaIndex=bestGammaIndex,cIndex=bestCIndex,
                gammaScle=gammaScale,cScale=Cscale,kernel=i)
        #储存模型
        clf = svm.SVC(kernel=i,C=bestC,gamma=bestGamma,shrinking=false)
        with open('./bestModels/'+str(i)+'_'+str(bestC)+'_'+str(bestGamma)+'.pkl','wb') as f:
            pickle.dump(clf,f)
main()