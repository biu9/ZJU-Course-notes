#include<omp.h>
#include<stdio.h>
int count = 0;
int findArray[10000] = {0};

int find(int number,int* findArray){
    if(findArray[number] == 0)return number;
    else{
        return findArray[number] = find(findArray[number],findArray);
    }
}

void Union(int num1,int num2){
    findArray[num2] = num1;
}

int main(){
    int number;
    char operate,ch;
    int num1,num2;
    int flag = 1;
    int count = 0;

    scanf("%d",&number);
    ch = getchar();
    //operate = getchar();
    while((operate = getchar()) != 'S'){
        if(operate == 'C'){
            scanf("%d",&num1);
            scanf("%d",&num2);
            if(find(num1,findArray) == find(num2,findArray)){
                printf("yes\n");
            }
            else{
                printf("no\n");
            }
        }
        else if (operate == 'I')
        {
            scanf("%d",&num1);
            scanf("%d",&num2);
            Union(num1,num2);
        }
        ch = getchar();
    }
    
    #pragma omp parallel for
    for(int i = 1;i<=number;i++){
        if(findArray[i] == 0)
            count++;
    }
    if(count == 1)
        printf("The network is connected.");
    else{
        printf("There are %d components.",count);
    }
}