from statistics import mode
from turtle import color
from sklearn import datasets
import numpy as np
import matplotlib.pyplot as plt
from sklearn import linear_model
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split


iris = datasets.load_iris()
X = iris["data"][:,3:]
Y = (iris["target"] == 2).astype(np.int)#1 if target , 0 else

X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.1, random_state=0)

model = linear_model.LogisticRegression()
model.fit(X_train, Y_train)

truthRate = model.score(X_test, Y_test)

print(truthRate)

for i in np.arange(0,3,0.001):
    plt.plot(i,model.predict_proba(i.reshape(1,-1))[0][0],'b.')
    plt.plot(i,model.predict_proba(i.reshape(1,-1))[0][1],'r.')
plt.show()