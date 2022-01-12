#include<stdio.h>

//使用logistic模型进行预测
//使用欧拉方法近似解logistic模型
//y(0) = 10
//求t=7时的y(t)
//y'(t) = k*y(t)*(1-y(t)/L)
//k = 0.8

double fn(double t,double y,double k,double L){
    double res = 0;
    res = k*y*(1-y/L);
    return res;
}

int main(){
    int N = 1000000;
    double k = 0.8;
    int L = 2000;
    double h = (4.0-0)/N;
    double t = 0;
    double y = 10;
    int iterateTime = 0;
    //printf("第%d次迭代，t = %lf,y = %lf\n",iterateTime,t,y);
    for(double j = 0;j<0.8;j+=0.001){
        for(int i=0;i<N;i++){
            t += h;
            double tmp = y;
            y = tmp + h*fn(t,tmp,j,L);
            iterateTime++;
            //printf("第%d次迭代，t = %lf,y = %lf\n",iterateTime,t,y);
        }
        printf("k = %lf时迭代得到的结果，t = %lf,y = %lf\n",j,t,y);
        if(y>=40)
            break;
        t = 0;
        y = 10;
    }
}