import MY_KNN
import numpy as np

group,labels =MY_KNN.creatDataSet()
print(MY_KNN.classify0([0,0],group,labels,3))
print(MY_KNN.classify0([0.8,0.7],group,labels,3))
