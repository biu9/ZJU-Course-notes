from turtle import color
import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import LatentDirichletAllocation

def createData():
    A = np.random.uniform(low=10,high=13,size=(30,2))
    B = np.random.uniform(low=15,high=18,size=(30,2))

    return A,B

def train(A,B):
    lda = LatentDirichletAllocation(n_components=2,max_iter=3,learning_method='online',learning_offset=500.,random_state=0)
    Anew = lda.fit_transform(A)
    Bnew = lda.fit_transform(B)
    return Anew,Bnew

def myLDA(A,B):
    A_1 = np.mean(A,axis=0)
    B_1 = np.mean(B,axis=0)
    Sw1 = np.dot((A-A_1).T,(A-A_1))
    Sw2 = np.dot((B-B_1).T,(B-B_1))
    Sw = Sw1 + Sw2
    tmp = np.array(A_1-B_1)
    Sb = np.dot(tmp.reshape(2,1),tmp.reshape(1,2))
    #获得Sw^-1 * Sb
    res = np.dot(np.linalg.inv(Sw),(Sb))
    #获得特征值和特征向量
    eig_value,eig_vector = np.linalg.eig(res)
    #获得特征值排序
    idx = eig_value.argsort()[::-1]
    w = eig_vector[:,idx[0]]
    #获取w^T * A
    Anew = np.zeros((30,2))
    for i in range(len(A)):
        Anew[i] = np.dot(w.reshape(1,2),A[i].reshape(2,1))
    #获取w^T * B
    Bnew = np.zeros((30,2))
    for i in range(len(B)):
        Bnew[i] = np.dot(w.reshape(1,2),B[i].reshape(2,1))
    plt.plot(-Anew[:,0]-5,-Anew[:,1]-5,color='red')
    plt.plot(-Bnew[:,0]-7,-Bnew[:,1]-7,color='blue')
    plt.plot(A[:,0],A[:,1],'ro')
    plt.plot(B[:,0],B[:,1],'bo')
    plt.show()

def plot(A,B,Anew,Bnew):
    fig = plt.figure()
    ax1 = fig.add_subplot(211)
    ax2 = fig.add_subplot(212)
    ax1.plot(A[:,0],A[:,1],'ro')
    ax1.plot(B[:,0],B[:,1],'bo')
    ax2.plot(Anew[:,0],Anew[:,1],color='red')
    ax2.plot(Bnew[:,0],Bnew[:,1],color='blue')
    #plt.show()

def main():
    A,B = createData()
    Anew,Bnew = train(A,B)
    #plot(A,B,Anew,Bnew)
    myLDA(A,B)

main()