#include<stdio.h>

//使用logistic模型进行预测
//使用欧拉方法近似解logistic模型
//y(0) = 10
//求t=7时的y(t)
//y'(t) = k*y(t)*(1-y(t)/L)
//k = 0.8

double fn(double t,double y){
    double res = 0;
    res = 0.8*y*(1-y/2000);
    return res;
}

int main(){
    int N = 1000000;
    double h = (7.0-0)/N;
    double t = 0;
    double y = 10;
    int iterateTime = 0;
    //printf("第%d次迭代，t = %lf,y = %lf\n",iterateTime,t,y);
    for(int i=0;i<N;i++){
        t += h;
        double tmp = y;
        y = tmp + h*fn(t,tmp);
        iterateTime++;
        //printf("第%d次迭代，t = %lf,y = %lf\n",iterateTime,t,y);
    }
        printf("第%d次迭代，t = %lf,y = %lf\n",iterateTime,t,y);
}