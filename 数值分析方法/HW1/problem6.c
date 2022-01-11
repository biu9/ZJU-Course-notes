//fixed point iteration
#include <stdio.h>
#include <math.h>

double function(float x){
    return sqrt(exp(x)/3.0);
}

int main(){
    double a = 1;
    double b = 2;
    double c = 1;
    int count = 0;
    while(fabs(function(c)-c)>0.01){
        c=function(c);
        printf("第%d次迭代，求得的解为%lf\n",count++,c);
    }
    printf("最终解为:%lf\n",c);
    
}