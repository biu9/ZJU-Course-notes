#include<stdio.h>

int main(){
    int i,j=0,cnt =0 ;
    int A[10000] = {0};
    for(int i=0;i<10000;i++)
        A[i] = 0;
    int runTimes = 0;
    for(i = 0;i<10000;++i){
        for(;j<10000;++j){
            //cnt += j - i;
            runTimes++;
        }
    }
    printf("%ld",runTimes);
}