#include<stdio.h>
#include<math.h>
double fn(int x){
    return 2.711864407*x+4.542372881;
}

int main(){
    int x[4] = {0,2,4,5};
    int y[4] = {6,8,14,20};
    double E=0;
    for(int i=0;i<4;i++){
        E+=pow(fn(x[i])-y[i],2);
    }
    printf("%f\n",E);
}