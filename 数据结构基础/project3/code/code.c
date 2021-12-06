#include<stdio.h>
int printIndex = 0;

/*
函数名：scan
函数功能：扫描输入，并将输入的图以二维矩阵的形式存储在数组中
函数参数：Na表示请求点的数量，Ns表示派遣中心的数量，Num数组储存每个派遣中心的车的数量，request表示请求点数组
*/
void scan(int* Na,int* Ns,int* Num,int map[][100],int* request,int* requestArray){
    scanf("%d",Na);
    scanf("%d",Ns);
    int max;
    for(int i=0;i<*Ns;i++){
        scanf("%d",&Num[i]);
    }
    scanf("%d",&max);
    for(int i = 0;i<max;i++){
        char ch = getchar();
        ch = getchar();
        if(ch == 'A'){//如果第一个输入是A
            ch = getchar();//去除-;
            int x,y,time;
            scanf("%d %d %d",&x,&y,&time);
            //printf("%d %d %d\n",x,y,time);
            map[x][y+*Ns] = time;
            map[y+*Ns][x] = time;
        }
        else{
            int x = ch - '0';
            ch = getchar();
            ch = getchar();
            if(ch == 'A'){//如果第二个是A开头
                ch = getchar();
                int y,time;
                scanf("%d %d",&y,&time);
                //printf("%d %d %d\n",x,y,time);
                map[x+*Ns][y] = time;
                map[y][x+*Ns] = time;
            }
            else{
                int y = ch - '0';
                int time;
                scanf("%d",&time);
                //printf("%d %d %d\n",x,y,time);
                map[x+*Ns][y+*Ns] = time;
                map[y+*Ns][x+*Ns] = time;
            }
        }
    }
    //输入请求点
    scanf("%d ",request);
    for(int i=0;i<*request;i++){
        scanf("%d",&requestArray[i]);
    }
}

/*
函数名：Dijkstra
函数功能：Dijkstra算法，计算每个点到派遣中心的最短距离
函数参数：map：以二维矩阵形式表示的图，start：起始点，end：终点，minDistance：距离数组，path：路径数组
*/
void Dijkstra(int map[][100],int start,int verticeNum,int* minDistance,int* path){
    //int minDistance[100];//记录原点到各点的最短距离
    int min = 100,minIndex;
    int visited[100] = {0};//记录该点是否已经是最短路径
    minDistance[start] = 0;//起始点到起始点的距离为0
    visited[start] = 1;//起始点到起始点是最短路径
    //dijiestra算法
    for(int i = 0;i<verticeNum;i++){
        if(map[start][i] == 0){
            minDistance[i] = 10000;
        }
        else{
            minDistance[i] = map[start][i];
        }
    }

    for(int i=0;i<verticeNum;i++){
        min = 100;//初始化最小距离为100
        for(int j=0;j<verticeNum;j++){//遍历所有点
            if(!visited[j] && minDistance[j]<min){//如果该点未被访问过且距离小于最小距离
                min = minDistance[j];//更新最小距离
                minIndex = j;//记录最小距离的点
            }
        }
        //printf("minIndex = %d, min = %d\n",minIndex,min);

        visited[minIndex] = 1;//将最小距离的点设置为已访问
        for(int j=0;j<verticeNum;j++){//遍历所有点
            if(!visited[j] && map[minIndex][j]>0 && minDistance[minIndex]+map[minIndex][j]<minDistance[j]){//如果该点未被访问过且距离小于最小距离
                minDistance[j] = minDistance[minIndex]+map[minIndex][j];//更新最小距离
                path[j] = minIndex;//记录最小距离的点
               // printf("path[%d] = %d\n",j,minIndex);
            }
        }
    }
}

/*
判断选择哪个派遣中心出车，判断规则如下
1、选取有车剩余的派遣中心
2、选取耗时最短的派遣中心
3、选取经过街道数目最少的派遣中心
num表示接车点的编号
函数输入：minDistance数组表示每个点到起始点的最短时间，path数组表示每个点到起始点的最短路径，
        Num数组表示每个派遣中心点的车辆数目,Ns表示派遣中心的数量(从1开始编号)
        requestArray[num]表示请求点的编号
要求：根据上述几条规则选择出车的派遣中心，每派出一辆车，Num[i]--,i表示派遣中心编号,并在judge函数中输出出车的派遣中心编号，
        出车的派遣中心首先要满足有车(Num[i]>0)，然后要满足耗时最短，如果有多个出车点耗时相同，
        则优先选择剩余车多的出车点，
        如果剩余车多的出车点还有多个，则优先选择经过街道数目最少的出车点。
*/
void judge(int* minDistance,int* Num,int* path,int* requestArray,int num,int Ns,int* print){
    int flag[100][100];
    int res = 0;
    int ALLBUSY = 1;
    int minStrPassed = 100;//minStreetPassedCenter
    int minStrPassedCenter = 0;
    int minStrPassedCenterArray[100];
    int strPassedCount[100];
    for(int i = 0;i<100;i++)
        strPassedCount[i] = 0;
    //初始化flag数组
    for(int i = 0;i<Ns;i++){
        if(Num[i] > 0){
            flag[0][i+1] = 1;
            ALLBUSY = 0;
        }
        else{
            flag[0][i+1] = 0;
        }
    }
    if(ALLBUSY == 1){
        print[printIndex++] = 0;
        printf("all busy\n");  
        return;      
    }

    //初始化minStrPassedCenterArray数组
    int carLeftCenter[100];
    int carLeftIndex = 0;
    //初始化carLeftCenter数组
    for(int i = 0;i<Ns;i++){
        if(Num[i] > 0)
            carLeftCenter[carLeftIndex++] = i;
    }
    //如果没有中心有车则print all busy
    if(carLeftIndex == 0){
        print[printIndex++] = 0;
        printf("all busy\n");
        return;
    }
    else{//如果中心有车
    int minTime = 100;
    int minTimeCenter = 0;//时间最短的中心的数量
    int minTimeArray[100];//储存具有最短时间中心的数组
    for(int i = 0;i<carLeftIndex;i++){
        if(minDistance[carLeftCenter[i]+1] < minTime)
            minTime = minDistance[carLeftCenter[i]+1];
    }
    for(int i = 0;i<carLeftIndex;i++){
        if(minDistance[carLeftCenter[i]+1] == minTime){
            flag[1][carLeftCenter[i]+1] = 1;
            minTimeArray[minTimeCenter++] = carLeftCenter[i]+1;
            //printf("flag[1][%d] = 1\n",i+1);
        }
        else{
            flag[1][carLeftCenter[i]+1] = 0;
        }
    }
    if(minTimeCenter == 1){//如果只有一个中心时间最短
        Num[minTimeArray[0]-1]--;
        printf("res = A-%d",minTimeArray[0]);
        int j = minTimeArray[0];
            while (path[j] != 0){
                printf("->%d",path[j]-3);
                j = path[j];
                //printf("----------%d--------------",i-3);   
            }
            printf("->%d\n",requestArray[num-1]);
        print[printIndex++] = minTimeArray[0];
        return;
    }
    else {//如果有多个中心时间最短
        int maxCar = -100;
        int maxCarCenter = 0;//具有最多车的中心
        int maxCarArray[100];//储存具有最多车中心的数组
        for(int i = 0;i<minTimeCenter;i++){
            if(Num[minTimeArray[i]-1] > maxCar)
                maxCar = Num[minTimeArray[i]-1];                
        }
        for(int i = 0;i<minTimeCenter;i++){
            if(Num[minTimeArray[i]-1] == maxCar){
                maxCarArray[maxCarCenter++] = minTimeArray[i];
            }
        }
        if(maxCarCenter == 1){//如果只有一个中心最多车
            Num[maxCarArray[0]-1]--;
            printf("res = A-%d",maxCarArray[0]);
            int j = maxCarArray[0];
            while (path[j] != 0){
                printf("->%d",path[j]-3);
                j = path[j];
                //printf("----------%d--------------",i-3);   
            }
            printf("->%d\n",requestArray[num-1]);
            print[printIndex++] = maxCarArray[0];
            return;
        }
        else if(maxCarCenter > 1){//如果有多个中心最多车
            /*
            int minStrPassed = 100;//minStreetPassedCenter
            int minStrPassedCenter = 0;
            int minStrPassedCenterArray[100];
            int strPassedCount[100];
            */
            for(int i = 0;i<maxCarCenter;i++){
                int j = maxCarArray[i];
                while(path[j] != 0){
                    j = path[j];
                    strPassedCount[maxCarArray[i]]++;
                }
                //printf("strPassedCount[%d] = %d\n",maxCarArray[i],strPassedCount[maxCarArray[i]]);
            }
            for(int i = 0;i<maxCarCenter;i++){
                if(strPassedCount[maxCarArray[i]] < minStrPassed)
                    minStrPassed = strPassedCount[maxCarArray[i]];
            }
            for(int i = 0;i<maxCarCenter;i++){
                if(strPassedCount[maxCarArray[i]] == minStrPassed){
                    printf("res = A-%d",maxCarArray[i]);
                    int j = maxCarArray[i];
                    while (path[j] != 0){
                    printf("->%d",path[j]-3);
                    j = path[j];
                    //printf("----------%d--------------",i-3);   
                    }
                    printf("->%d\n",requestArray[num-1]);
                    print[printIndex++] = maxCarArray[i];
                    Num[maxCarArray[i]-1]--;
                    return;
                }
            }
        }
    }
    }
}

/*
函数名：output
函数功能：根据dijkstra算法排序以后的数组
*/
void output(int verticeNum,int map[][100],int* requestArray,int* path,int* minDistance,int Ns,int* Num){
    int print[100];
   for(int i = 4;i<verticeNum+1;i++){
        Dijkstra(map,requestArray[i-4]+Ns,verticeNum,minDistance,path);
        printf("对于第%d个请求点:\n",i-3);
        for(int k = 1;k<4;k++){
            printf("    到A-%d的最短时间为：%d,路径为:A-%d",k,minDistance[k],k);
            int j = k;
            while (path[j] != 0){
                printf("->%d",path[j]-3);
                j = path[j];
                //printf("----------%d--------------",i-3);   
            }
            printf("->%d",requestArray[i-4]);            
            printf("\n");
        }
        judge(minDistance,Num,path,requestArray,i-3,Ns,print);
        for(int i = 0;i<100;i++)
            path[i] = 0;        
    }   
}

int main(){
    int Na,Ns,Num[100] = {0};//Num[i]表示第i个派遣中心的车辆数
    int map[100][100];//map[i][j]表示从i到j的距离
    int request,requestArray[100];//requestArray[i]表示第i个请求点
    scan(&Na,&Ns,Num,map,&request,requestArray);//输入
    //test
    //printf("一共有%d个接车点\n",Na);
    //printf("一共有%d个救护中心\n",Ns);
    //for(int i=0;i<Ns;i++){
      //  printf("第%d个救护中心有%d辆车\n",i+1,Num[i]);
    //}
    //test map
    //for(int i = 1;i<Na+Ns+1;i++){
      //  for(int j = 1;j<Na+Ns+1;j++){
        //    printf("%d ",map[i][j]);
        //}
        //printf("\n");
    //}
    //map中1-Na为救护中心，Na-Na+Ns为接车点

    //test request
    //printf("一共有%d个请求点\n",request);
    //for(int i=0;i<request;i++){
      //  printf("第%d个请求点是%d\n",i+1,requestArray[i]);
    //}

    int minDistance[100];
    int path[100] = {0};
    int verticeNum = Na+Ns+1;//图中顶点数

    output(verticeNum,map,requestArray,path,minDistance,Ns,Num);//输出
}