#include<stdio.h>
/*
5 4
10 2 3 4 5
10 3 2 5 4
5 10 3 2 4
2 3 10 4 5
3 5 10 4 2
*/
//如果globalStack的头尾指针指向的数字都不等于number[i][j]且stackSp>=len,则输出no
//如果globalStack的头尾指针指向的数字都不等于number[i][j]且stackSp<len,push,再次判断
//如果globalStack的头指针指向的数字等于number[i][j],pop头指针,globalStack[globalHeadPtr--]=0
//如果globalStack的尾指针指向的数字等于number[i][j],pop尾指针,globalStack[globalTailPtr++]=0

int globalStack[100] = {0};
int gloablHeadPtr = 0;
int globalTailPtr = 0;
int stackSp = 0;
void scan(int* len,int* nums,int number[][100],int* stack){
    scanf("%d %d",len,nums);
    for(int i=0;i<*len;i++)
        scanf("%d",&stack[i]);
    for(int i=0;i<*nums;i++){
        for(int j=0;j<*len;j++){
            scanf("%d",&number[i][j]);
        }
    }
}

int push(int* stack,int lens){
    if(stackSp < lens){
        int tmp = gloablHeadPtr;
        globalStack[gloablHeadPtr++] = stack[stackSp++];       
        return 1;
    }
    else if(stackSp >= lens)
        return 0;
}

void pop_head(){
    globalStack[gloablHeadPtr--] = 0;
}

void pop_tail(){
    globalStack[globalTailPtr++] = 0;
}

int main(){
    int len,nums,number[100][100];
    int stack[100];
    scan(&len,&nums,number,stack);
    int flag = 1;
    for(int i=0;i<nums;i++){
        flag = 1;
        for(int j=0;j<len;j++){
            if(number[i][j] != globalStack[gloablHeadPtr-1] && number[i][j] != globalStack[globalTailPtr]){
                while(1){
                    flag = push(stack,len);
                    if(flag == 0)
                        break;
                    if(number[i][j] == globalStack[gloablHeadPtr-1]){
                        pop_head();
                        break;
                    }               
                }
                if(flag == 0)
                    break;
            }
            else if(number[i][j] == globalStack[gloablHeadPtr-1]){
                pop_head();
            }
            else if(number[i][j] == globalStack[globalTailPtr]){
                pop_tail();
            }
        }
        if(flag == 0){
            printf("no");            
        }
        else if(flag == 1){
            printf("yes");            
        }
        if(i != nums-1)
            printf("\n");
        stackSp = 0;
        gloablHeadPtr = 0;
        globalTailPtr = 0;
        for(int i=0;i<100;i++)
            globalStack[i] = 0;
    }
}