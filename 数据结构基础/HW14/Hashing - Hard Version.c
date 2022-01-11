#include<stdio.h>

int main(){
    int N;
    int hashed[1000];
    int initial[1000] = {0};
    int flag[1000] = {0};
    int max = -1;
    int min = 10000;
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%d",&hashed[i]);                                      
        if(max < hashed[i])
            max = hashed[i];
        if(min > hashed[i] && hashed[i] >= 0)
            min = hashed[i];
    }
    for(int i=0;i<N;i++){
        for(int j=min;j<max;j++){
            if(flag[j%N] == 0){
                if(hashed[j%N] == j){
                    initial[i] = j;  
                    flag[j%N] = 1; 
                    break;                    
                }
            }
            else{
                for(int k=j%N;k<N;k++){
                    if(hashed[k] == j){
                        initial[i] = j;
                        flag[k] = 1;
                        break;
                    }
                }
            }
        }
    }
    for(int i=0;i<N;i++){
        printf("%d ",initial[i]);
    }
}