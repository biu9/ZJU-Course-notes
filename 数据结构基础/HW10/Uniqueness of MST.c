#include<stdio.h>

int findArray[50000] = {0};

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
    //sort weight
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
}

int main(){
    int x[50000],y[50000],weight[50000],edge,vertice;
    int totalFlow = 0;
    int visited[50000] = {0};
    int flag = 0;
    int flagNoMst = 0;

    scan(x,y,weight,&edge,&vertice);
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
    if(flagNoMst == 0){
        printf("%d\n",totalFlow);
        if(flag == 1)
            printf("No\n");
        else
            printf("Yes\n");
    }
    else{
        printf("No Mst\n");
        printf("%d",flagNoMst+1);
    }

}