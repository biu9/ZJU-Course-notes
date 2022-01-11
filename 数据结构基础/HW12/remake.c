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
        int changeNum;//插入的数字
        int changeIndex;
        int insTmp[100] = {-1};
        int insTmpIndex = 0;
        int insFlag = 1;
        for(int i=0;i<number-1;i++){
            if(tmp[i] > tmp[i+1]){
                changeNum = tmp[i+1];
                changeIndex = i+1;
                break;
            }
        }
        for(int i=0;i<number;i++){
            if(tmp[i] < changeNum && tmp[i+1] > changeNum && insFlag){
                insTmp[insTmpIndex+1] = changeNum;
                insTmp[insTmpIndex++] = tmp[i];
                insTmpIndex ++;
                insFlag = 0;
            }
            else if(i == changeIndex){
                continue;
            }
            else{
                insTmp[insTmpIndex++] = tmp[i];
            }
        }
        //printf("changeNum = %d,changeIndex = %d\n",changeNum,changeIndex);
        for(int i=0;i<number;i++){
            if(i == number-1)
                printf("%d",insTmp[i]);
            else
                printf("%d ",insTmp[i]);            
        }
    }
}