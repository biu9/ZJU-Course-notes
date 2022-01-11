#include<stdio.h>
#include<math.h>
#define TOL 0.001

int main(){
    double x[100][100] = {
        {10,-1,0,9},
        {-1,10,-2,7},
        {0,-2,10,6},
    };
    double x1,x2,x3;    
    double xTmp1,xTmp2,xTmp3;
    double sumTmp = 0;
    x1 = x2 = x3 = 0;
    int i=0;
    double maxNorms = 10;
    while(maxNorms > TOL){
        xTmp1 = (-(x[0][1]*x2+x[0][2]*x3)+x[0][3])/x[0][0];
        xTmp2 = (-(x[1][0]*xTmp1+x[1][2]*x3)+x[1][3])/x[1][1];
        xTmp3 = (-(x[2][0]*xTmp1+x[2][1]*xTmp2)+x[2][3])/x[2][2];
        maxNorms = fabs(xTmp1-x1);
        if(fabs(xTmp2-x2)>maxNorms)
            maxNorms = fabs(xTmp2-x2);
        if(fabs(xTmp3-x3)>maxNorms)
            maxNorms = fabs(xTmp3-x3);
        //printf("maxNorms: %f\n",maxNorms);
        x1 = xTmp1;
        x2 = xTmp2;
        x3 = xTmp3;
        i++;
        printf("第%d次迭代:x1=%f,x2=%f,x3=%f\n",i,x1,x2,x3);
    }
    printf("最终迭代结果:x1=%f,x2=%f,x3=%f\n",x1,x2,x3);
}