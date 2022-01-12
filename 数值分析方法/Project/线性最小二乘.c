#include<stdio.h>
//使用线性最小二乘拟合以下数据
//y: 1 43 75 155 196 219 271 318 351 385 425 466 503 537 575 599 626
//x: 1761 1767 1771 1772 1774 1775 1777 1779 1780 1782 1783 1785 1786 1788 1789 1791 1791
int main(){
    int x[17] = {1761,1767,1771,1772,1774,1775,1777,1779,1780,1782,1783,1785,1786,1788,1789,1791,1791};
    int y[17] = {1,43,75,155,196,219,271,318,351,385,425,466,503,537,575,599,626};
    double a0,a1;
    double m = 17;
    double sumXi = 0,sumYi=0,sumXi2=0,sumYi2=0,sumXiYi=0;
    for(int i=0;i<17;i++){
        sumXi += x[i];
        sumYi += y[i];
        sumXi2 += x[i]*x[i];
        sumYi2 += y[i]*y[i];
        sumXiYi += x[i]*y[i];
    }
    a1 = (m*sumXiYi-sumXi*sumYi)/(m*sumXi2-sumXi*sumXi);
    a0 = (sumXi2*sumYi-sumXiYi*sumXi)/(m*sumXi2-sumXi*sumXi);
    printf("a0 = %f\na1 = %f\n",a0,a1);
    //y=173时预测x
    printf("y=173时预测x = %f\n",(173-a0)/a1);
    //y=726时预测x
    printf("y=726时预测x = %f\n",(726-a0)/a1);
}