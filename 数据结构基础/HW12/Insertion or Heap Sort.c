#include<stdio.h>

void scan(int* number,int* start,int* tmp){
    scanf("%d",number);
    for(int i=0;i<*number;i++){
        scanf("%d",&start[i]);
    }
    for(int i=0;i<*number;i++){
        scanf("%d",&tmp[i]);
    }
}

int main(){
    int number;
    int min = 100,max = -1;
    int start[100],tmp[100];
    scan(&number,start,tmp);
    for(int i=0;i<number;i++){
        if(start[i] > max)
            max = start[i];
        else if(start[i] < min)
            min = start[i];
    }
    if(tmp[number-1] == max){
        printf("Heap Sort\n");
        int exchange = tmp[0];
        int tmpHeap[100];
        int exchangeIndex = 0;
        for(int i=0;i<number-1;i++){
            if(tmp[i] < exchange && tmp[i+1] > exchange){
                exchangeIndex = i;
                tmpHeap[i] = exchange;
            }
        }
        int dad = 0;
        int son = 2*dad+1;
        while(son < exchange){
            if(son+1 < exchangeIndex && tmp[son] < tmp[son+1])
                son++;
            
        }
        
    }
    else{
        printf("Insertion Sort\n");
        int exchange = 0;
        int tmp1[100];
        for(int i=1;i<number;i++){
            if(tmp[i] < tmp[i-1]){
                exchange = tmp[i];
                break;
            }
        }
        for(int i=0;i<number-1;i++){
            if(tmp[i] < exchange && tmp[i+1] > exchange){
                tmp1[i+1] = exchange;
                int k=i+1;
                for(int j=i+1;j<number-1;j++){
                    if(tmp[j] != exchange)
                        tmp1[++k] = tmp[j];
                    else{
                        j++;
                        tmp1[++k] = tmp[j];
                    }
                }
                for(int m=i+1;m<number;m++){
                    tmp[m] = tmp1[m];
                }
                break;
            }
        }
        for(int i=0;i<number;i++){
            if(i == number-1)
                printf("%d",tmp[i]);
            else
                printf("%d ",tmp[i]);          
        }
    }
}