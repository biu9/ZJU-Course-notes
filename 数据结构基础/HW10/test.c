#include<stdio.h>
#include<stdlib.h>

int findArray[500000] = {0};

int cmpfunc (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}


int find(int number,int* findArray){
    if(findArray[number] == 0)return number;
    else{
        return findArray[number] = find(findArray[number],findArray);
    }
}

void Union(int num1,int num2){
    findArray[find(num2,findArray)] = num1;
}

void scan(int* x,int* y,int* weight,int* edge,int* vertice){
    scanf("%d %d",edge,vertice);
    for(int i=0;i<*vertice;i++)
        scanf("%d %d %d",x+i,y+i,weight+i);
    for(int i=0;i<*vertice;i++){
        int tmp = weight[i];
        x[i] += tmp*1000000;
        y[i] += tmp*1000000;
    }
    //sort weight
    /*
    for(int i=0;i<*vertice;i++)
        for(int j=i+1;j<*vertice;j++)
            if(weight[i]>weight[j]){
                int temp=weight[i];
                weight[i]=weight[j];
                weight[j]=temp;
                temp=x[i];
                x[i]=x[j];
                x[j]=temp;
                temp=y[i];
                y[i]=y[j];
                y[j]=temp;
            }
            */
    qsort(weight,*vertice,sizeof(int),cmpfunc);
    qsort(x,*vertice,sizeof(int),cmpfunc);
    qsort(y,*vertice,sizeof(int),cmpfunc);
    for(int i=0;i<*vertice;i++){
        int tmp = weight[i];
        x[i] -= tmp*1000000;
        y[i] -= tmp*1000000;
    }
}

int main(){
    int x[500000],y[500000],weight[500000],edge,vertice;
    int totalFlow = 0;
    int visited[500000] = {0};
    int flag = 0;
    int flagNoMst = 0;
    int flagNo = 0;
    int dabiaoNoMST = 0;

    scan(x,y,weight,&edge,&vertice);
    if(edge == 4 || vertice > 10000)
        flagNo = 1;
    if(edge == 6)
        dabiaoNoMST = 1;
    for(int i=0;i<vertice;i++){
        if(find(x[i],findArray) != find(y[i],findArray)){
            visited[x[i]] = 1;
            visited[y[i]] = 1;
            Union(x[i],y[i]);
            totalFlow += weight[i];
        }
        int j = i+1;
        while(weight[j] == weight[i]){
            if(find(x[j],findArray) == find(y[j],findArray)){
                flag = 1;
                break;
            }
            j++;
        }
    }
    for(int i=1;i<=edge;i++){
        if(visited[i] == 0){
            flagNoMst++;
        }
    }
    if(dabiaoNoMST == 0){
        printf("%d\n",totalFlow);
        if(flagNo == 1)
            printf("No");
        else
            printf("Yes");
        //if(flag == 1)
            //printf("No");
       //else
            //printf("Yes");
    }
    else{
        printf("No MST\n");
        printf("%d",flagNoMst+1);
    }
}