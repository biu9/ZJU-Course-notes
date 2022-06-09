from mimetypes import init
import numpy as np
import matplotlib.pyplot as plt

# 使用Batch和delta规则训练神经网络
def batch(w_current,learning_rate,gradient,x_current):
    """
    :param w_current: 当前权重
    :param learning_rate: 学习率
    :param gradient: 梯度
    :param x_current: 当前样本
    :return: 更新后的权重
    """
    w_new = w_current + learning_rate * gradient*x_current
    return w_new

def calculateDw(y_predict,y,x_i):
    """
    :param y_predict: 预测值
    :param y: 真实值
    :param x_i: 当前样本
    :return: 梯度
    """
    dw = sigmoid(y_predict)*(1-sigmoid(y_predict))*(y-y_predict)*x_i
    return dw

def sigmoid(x):
    """
    :param x: 输入
    :return: sigmoid函数
    """
    return 1/(1+np.exp(-x))

def train(train_data,train_labels,learning_rate,iteration):
    """
    :param train_data: 训练数据
    :param train_labels: 训练标签
    :param learning_rate: 学习率
    :param iteration: 迭代次数
    :return: 权重
    """
    w = np.zeros(len(train_data[0]))
    for i in range(iteration):
        #对于每一个输入进行训练
        wSum = np.zeros(len(train_data[0]))
        for j in range(0,len(train_data[0]),1):
            #计算梯度
            gradient = calculateDw(np.dot(w,train_data[j]),train_labels[j],train_data[j])
            #更新权重
            wTmp = batch(w,learning_rate,gradient,train_data[j])
            wSum += wTmp
        wSum = wSum/len(train_data[0])
        w = wSum
    return w

def main():
    train_data = np.array([
        [0,0,1],
        [0,1,1],
        [1,0,1],
        [1,1,1]        
    ]
    )
    train_labels = np.array([0,0,1,1])
    learning_rate = 0.01
    #iteration = 10000
    for iteration in range(0,500,1):
        w = train(train_data,train_labels,learning_rate,iteration)
        predict_res = predict(w,train_data)
        drawLoss(predict_res,iteration,train_labels)
    plt.show()
    print("w = ",w)
    res = predict(w,train_data)
    print("res = ",res)
    mse = np.mean(np.square(res-train_labels))
    print("mse = ",mse)

def predict(w,predict_data):
    """
    :param w: 权重
    :param predict_data: 预测数据
    :return: 预测结果
    """
    predict_labels = []
    for i in range(len(predict_data)):
        predict_labels.append(np.dot(w,predict_data[i]))
    return predict_labels

def drawLoss(predict_res,iteration,train_labels):
    """
    :param predict_res: 预测结果
    :return: 显示图像
    """
    #计算均方误差
    mse = np.mean(np.square(predict_res-train_labels))
    plt.plot(iteration,mse,'ro')

main()
    
