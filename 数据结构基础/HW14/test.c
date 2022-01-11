#include<stdio.h>

int main(){
    int N;
    scanf("%d",&N);
    int hashed[1000] = {0};
    int max = -1,min = 10000;
    int res[1000] = {0};
    int flag[1000] = {0};
    int breakFlag = 0;
    int fillFlag = 0;
    int count = 0;
    int fillResFlag[100] = {0};
    for(int i=0;i<N;i++){
        scanf("%d",&hashed[i]);   
        if(max < hashed[i])
            max = hashed[i];
        if(min > hashed[i] && hashed[i] >= 0)
            min = hashed[i];
        if(hashed[i] == -1)
            count++;     
    }
    //test
    //printf("%d %d",min,max);
    for(int i=0;i<N;i++){
        fillFlag = 0;
        for(int j=min;j<=max;j++){
            if(flag[j%N] == 0){
                if(hashed[j%N] == j){
                    //fillResFlag[j%N] = 1;
                    res[i] = j;
                    flag[j%N] = 1;
                    fillFlag = 1;
                    break;                    
                }
            }
            else if(flag[j%N] == 1){
                for(int k=j%N+1;k<N;k++){
                    if(hashed[k] == j && flag[k] == 0){
                        //printf("%d test\n",i);
                        res[i] = j;
                        fillFlag = 1;
                        flag[k] = 1;
                        breakFlag = 1;
                        break;
                    }                    
                    if(flag[k] == 0){
                        //breakFlag = 1;
                        break;
                    }
                }
            }
            if(breakFlag == 1){
                breakFlag = 0;
                break;
            }
        }
//===============================================
            if(res[i] == 0){
                for(int j=0;j<N;j++){
                    if(flag[j] == 0 && hashed[j] != -1){
                        res[i] = hashed[j];  
                        break;                      
                    }
                }
            }
//===============================================
    }
    for(int i=0;i<N-count;i++){
        if(i != N-count-1)
            printf("%d ",res[i]);
        else
            printf("%d",res[i]);
    }
}