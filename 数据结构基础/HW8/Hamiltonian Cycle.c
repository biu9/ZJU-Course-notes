#include<stdio.h>

int main(){
    int vertices,edge;
    scanf("%d %d",&vertices,&edge);
    int adj[201][201];
    int flag = 1;

    for(int i=0;i<201;i++){
        for(int j=0;j<201;j++){
            adj[i][j]=0;
        }
    }

    for(int i = 0;i<edge;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        adj[x][y] = 1;
    }

    //test
    for(int i = 0;i<vertices+1;i++){
        for(int j = 0;j<vertices+1;j++){
            //printf("%d ",adj[i][j]);
        }
        //printf("\n");
    }

    int inputNumber;
    scanf("%d",&inputNumber);
    for(int i = 0;i<inputNumber;i++){
        int num;
        scanf("%d",&num);
        //printf("num = %d\n",num);
        int visited[201] = {0};
        int check[201];
        for(int j = 0;j<num;j++){
            scanf("%d",&check[j]);  
            visited[check[j]] = 1;          
        }
        for(int k = 0;k<num-1;k++){
            if((adj[check[k]][check[k+1]] || adj[check[k+1]][check[k]]) == 0){
                //printf("check[%d][%d] = %d; k = %d\n",check[k],check[k+1],adj[check[k]][check[k+1]],k);
                flag = 0;
                break;
            }
        }
        if(check[0] != check[num-1])
            flag = 0;
        for(int i = 1;i<num;i++){
            if(visited[i] == 0){
                //printf("visited[%d] = 0\n",i);
                flag = 0;
                break;
            }
        }
        
        if(flag == 0){
            printf("NO");
            if(i != inputNumber-1)
                printf("\n");
        }
        else{
            printf("YES");
            if(i != inputNumber-1)
                printf("\n");            
        }

        flag = 1;
    }
}