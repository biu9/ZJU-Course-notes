//bisection method
#include <stdio.h>
#include <math.h>

float function(float x){
    float res = x*cos(x)-2*pow(x,2)+3*x-1;
    return res;
}

int main(){
    float a = 1.2;
    float b = 1.3;
    float c = (a+b)/2;
    double accuracy = 0.00001;
    int count = 0;
    while(fabs(function(c))>accuracy){
        if(function(a)*function(c)<0){
            b = c;
        }
        else{
            a = c;
        }
        printf("第%d次迭代,求得的解为%lf\n",count++,c);
        c = (a+b)/2;
    }
    printf("最终解为%lf",c);
}