#include<stdio.h>
#include<math.h>

int main(){
    double max = 0;
    for(double i=2;i<2.4;i+=0.0001){
        if(fabs((i-2)*(i-2.4)*(i-2.6)) > max)
            max = (fabs((i-2)*(i-2.4)*(i-2.6)));
    }
    printf("%f\n",max);
    printf("%lf\n",0.33576*0.016901);
}