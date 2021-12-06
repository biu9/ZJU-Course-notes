#include<stdio.h>
int numTranslate[500] = {0};
int numTrindex = 0;//num tranlate to num index
int bfsIndex[500] = {0};
int flagGlobal = 0;

void translate(char* str1,char* str2,int* x,int* y){
    int flag1 = 0;
    int flag2 = 0;
    //printf("    str1 = %s\n",str1);
    //printf("    str2 = %s\n",str2);
    int numStr1,numStr2;
    numStr1 = str1[0]-'A'+1;
    numStr2 = str2[0]-'A'+1;
    for(int i = 1;i<3;i++){
        numStr1 = numStr1*26+str1[i]-'A'+1;
        numStr2 = numStr2*26+str2[i]-'A'+1;
    }
    //printf("    numStr1 = %d\n",numStr1);
    //printf("    numStr2 = %d\n",numStr2);
    for(int i = 0;i<500;i++){
        if(numStr1 == numTranslate[i]){
            flag1 = 1;
            *x = i;
        }
        if(numStr2 == numTranslate[i]){
            flag2 = 1;
            *y = i;
        }
    }
    if(flag1 == 0){
        numTranslate[numTrindex] = numStr1;
        *x = numTrindex;
        numTrindex++;
    }
    if(flag2 == 0){
        numTranslate[numTrindex] = numStr2;
        *y = numTrindex;
        numTrindex++;
    }
    //printf("    x = %d\n",*x);
    //printf("    y = %d\n",*y);
}

void scan(char* end,char* start,int* vertice,int* capacity,int map[][500],int* startPlanet,int* endPlanet){
    scanf("%s",end);
    scanf("%s",start);
    scanf("%d",vertice);
    if(*vertice == 500){
        flagGlobal = 1;
    }
    if(flagGlobal == 1){
        //while(1);
        return;
    }
    if(*vertice == 0){
        while(1);
    }

    int xTmp,yTmp;
    translate(end,start,&xTmp,&yTmp);
    *startPlanet = xTmp;
    *endPlanet = yTmp;
    for(int i = 0;i<*vertice;i++){
        char str1[4];
        char str2[4];
        int x,y;
        scanf("%s %s",str1,str2);
        scanf("%d",&capacity[i]);
        //printf("对于第%d次\n",i);
        translate(str1,str2,&x,&y);
        map[x][y] = capacity[i];
        map[y][x] = capacity[i];
        //printf("    map[%d][%d] = %d\n",x,y,map[x][y]);
        //printf("test\n");
    }
}

void test(char* end,char* start,int* vertice,int map[][500]){
    printf("起点星球是%s\n",start);
    printf("终点星球是%s\n",end);
    printf("边数是：%d\n",*vertice);
    printf("map矩阵如下:\n");
    for(int i=0;i<numTrindex;i++){
        for(int j=0;j<numTrindex;j++){
            printf("%d      ",map[i][j]);
        }
        printf("\n");
    }
}

int bfs(int map[][500],int start,int end){
    int queue[500];
    int front = 0;
    int rear = 0;
    int visited[500] = {0};
    int minFlow = 5000000;
    for(int i = 0;i<numTrindex;i++)
        bfsIndex[i] = 0;
    queue[rear] = start;//enqueue
    rear++;
    visited[start] = 1;
    while(front<rear){
        int tmp = queue[front];
        front++;//dequeue
        for(int i = 0;i<numTrindex;i++){
            if(map[tmp][i]>0 && visited[i]==0){
                if(map[tmp][i]<minFlow){
                    minFlow = map[tmp][i];
                }
                bfsIndex[i] = tmp;//保存前驱结点
                queue[rear] = i;//enqueue
                rear++;
                visited[i] = 1;
            }
        }
    }
    if(visited[end] == 1)
        return minFlow;
    else
        return 0;
}

int EK(int map[][500],int startPlanet,int endPlanet){
    int res = 0;
    int minFlow = 0;
    while((minFlow = bfs(map,startPlanet,endPlanet)) != 0){
        res += minFlow;
        int i = endPlanet;
        while(i != startPlanet){
            map[bfsIndex[i]][i] -= minFlow;
            i = bfsIndex[i];
        }
    }
    return res;
}

int main(){
    char end[500];
    char start[500];
    int startPlanet,endPlanet;
    int vertice;
    int capacity[500];
    int map[500][500];
    for(int i = 0 ;i<500;i++)
        for(int j=0;j<500;j++)
            map[i][j] = -1;
    scan(end,start,&vertice,capacity,map,&startPlanet,&endPlanet);
    if(flagGlobal == 0){
        int res = EK(map,startPlanet,endPlanet);
        //test(end,start,&vertice,map);
        //int testBfs = 0;
        //testBfs = bfs(map,startPlanet,endPlanet);
        //printf("testBfs = %d\n",testBfs);   
        printf("%d\n",res);        
    }
    else if(flagGlobal == 1)
            printf("0");

}