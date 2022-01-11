#include<stdio.h>

int main(){
    double x[100][100] = {
        {-2,1,0.5,4},
        {1,-2,-0.5,-4},
        {0,1,2,0},
    };
    double x1,x2,x3;    
    double xTmp1,xTmp2,xTmp3;
    double sumTmp = 0;
    x1 = x2 = x3 = 0;
    int i=0;
    while(++i<10){
        xTmp1 = (-(x[0][1]*x2+x[0][2]*x3)+x[0][3])/x[0][0];
        xTmp2 = (-(x[1][0]*x1+x[1][2]*x3)+x[1][3])/x[1][1];
        xTmp3 = (-(x[2][0]*x1+x[2][1]*x2)+x[2][3])/x[2][2];
        x1 = xTmp1;
        x2 = xTmp2;
        x3 = xTmp3;
        printf("第%d次迭代:x1=%f,x2=%f,x3=%f\n",i,x1,x2,x3);
    }
}