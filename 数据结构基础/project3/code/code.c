#include<stdio.h>
int printIndex = 0;

/*
��������scan
�������ܣ�ɨ�����룬���������ͼ�Զ�ά�������ʽ�洢��������
����������Na��ʾ������������Ns��ʾ��ǲ���ĵ�������Num���鴢��ÿ����ǲ���ĵĳ���������request��ʾ���������
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
        if(ch == 'A'){//�����һ��������A
            ch = getchar();//ȥ��-;
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
            if(ch == 'A'){//����ڶ�����A��ͷ
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
    //���������
    scanf("%d ",request);
    for(int i=0;i<*request;i++){
        scanf("%d",&requestArray[i]);
    }
}

/*
��������Dijkstra
�������ܣ�Dijkstra�㷨������ÿ���㵽��ǲ���ĵ���̾���
����������map���Զ�ά������ʽ��ʾ��ͼ��start����ʼ�㣬end���յ㣬minDistance���������飬path��·������
*/
void Dijkstra(int map[][100],int start,int verticeNum,int* minDistance,int* path){
    //int minDistance[100];//��¼ԭ�㵽�������̾���
    int min = 100,minIndex;
    int visited[100] = {0};//��¼�õ��Ƿ��Ѿ������·��
    minDistance[start] = 0;//��ʼ�㵽��ʼ��ľ���Ϊ0
    visited[start] = 1;//��ʼ�㵽��ʼ�������·��
    //dijiestra�㷨
    for(int i = 0;i<verticeNum;i++){
        if(map[start][i] == 0){
            minDistance[i] = 10000;
        }
        else{
            minDistance[i] = map[start][i];
        }
    }

    for(int i=0;i<verticeNum;i++){
        min = 100;//��ʼ����С����Ϊ100
        for(int j=0;j<verticeNum;j++){//�������е�
            if(!visited[j] && minDistance[j]<min){//����õ�δ�����ʹ��Ҿ���С����С����
                min = minDistance[j];//������С����
                minIndex = j;//��¼��С����ĵ�
            }
        }
        //printf("minIndex = %d, min = %d\n",minIndex,min);

        visited[minIndex] = 1;//����С����ĵ�����Ϊ�ѷ���
        for(int j=0;j<verticeNum;j++){//�������е�
            if(!visited[j] && map[minIndex][j]>0 && minDistance[minIndex]+map[minIndex][j]<minDistance[j]){//����õ�δ�����ʹ��Ҿ���С����С����
                minDistance[j] = minDistance[minIndex]+map[minIndex][j];//������С����
                path[j] = minIndex;//��¼��С����ĵ�
               // printf("path[%d] = %d\n",j,minIndex);
            }
        }
    }
}

/*
�ж�ѡ���ĸ���ǲ���ĳ������жϹ�������
1��ѡȡ�г�ʣ�����ǲ����
2��ѡȡ��ʱ��̵���ǲ����
3��ѡȡ�����ֵ���Ŀ���ٵ���ǲ����
num��ʾ�ӳ���ı��
�������룺minDistance�����ʾÿ���㵽��ʼ������ʱ�䣬path�����ʾÿ���㵽��ʼ������·����
        Num�����ʾÿ����ǲ���ĵ�ĳ�����Ŀ,Ns��ʾ��ǲ���ĵ�����(��1��ʼ���)
        requestArray[num]��ʾ�����ı��
Ҫ�󣺸���������������ѡ���������ǲ���ģ�ÿ�ɳ�һ������Num[i]--,i��ʾ��ǲ���ı��,����judge�����������������ǲ���ı�ţ�
        ��������ǲ��������Ҫ�����г�(Num[i]>0)��Ȼ��Ҫ�����ʱ��̣�����ж���������ʱ��ͬ��
        ������ѡ��ʣ�೵��ĳ����㣬
        ���ʣ�೵��ĳ����㻹�ж����������ѡ�񾭹��ֵ���Ŀ���ٵĳ����㡣
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
    //��ʼ��flag����
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

    //��ʼ��minStrPassedCenterArray����
    int carLeftCenter[100];
    int carLeftIndex = 0;
    //��ʼ��carLeftCenter����
    for(int i = 0;i<Ns;i++){
        if(Num[i] > 0)
            carLeftCenter[carLeftIndex++] = i;
    }
    //���û�������г���print all busy
    if(carLeftIndex == 0){
        print[printIndex++] = 0;
        printf("all busy\n");
        return;
    }
    else{//��������г�
    int minTime = 100;
    int minTimeCenter = 0;//ʱ����̵����ĵ�����
    int minTimeArray[100];//����������ʱ�����ĵ�����
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
    if(minTimeCenter == 1){//���ֻ��һ������ʱ�����
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
    else {//����ж������ʱ�����
        int maxCar = -100;
        int maxCarCenter = 0;//������೵������
        int maxCarArray[100];//���������೵���ĵ�����
        for(int i = 0;i<minTimeCenter;i++){
            if(Num[minTimeArray[i]-1] > maxCar)
                maxCar = Num[minTimeArray[i]-1];                
        }
        for(int i = 0;i<minTimeCenter;i++){
            if(Num[minTimeArray[i]-1] == maxCar){
                maxCarArray[maxCarCenter++] = minTimeArray[i];
            }
        }
        if(maxCarCenter == 1){//���ֻ��һ��������೵
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
        else if(maxCarCenter > 1){//����ж��������೵
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
��������output
�������ܣ�����dijkstra�㷨�����Ժ������
*/
void output(int verticeNum,int map[][100],int* requestArray,int* path,int* minDistance,int Ns,int* Num){
    int print[100];
   for(int i = 4;i<verticeNum+1;i++){
        Dijkstra(map,requestArray[i-4]+Ns,verticeNum,minDistance,path);
        printf("���ڵ�%d�������:\n",i-3);
        for(int k = 1;k<4;k++){
            printf("    ��A-%d�����ʱ��Ϊ��%d,·��Ϊ:A-%d",k,minDistance[k],k);
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
    int Na,Ns,Num[100] = {0};//Num[i]��ʾ��i����ǲ���ĵĳ�����
    int map[100][100];//map[i][j]��ʾ��i��j�ľ���
    int request,requestArray[100];//requestArray[i]��ʾ��i�������
    scan(&Na,&Ns,Num,map,&request,requestArray);//����
    //test
    //printf("һ����%d���ӳ���\n",Na);
    //printf("һ����%d���Ȼ�����\n",Ns);
    //for(int i=0;i<Ns;i++){
      //  printf("��%d���Ȼ�������%d����\n",i+1,Num[i]);
    //}
    //test map
    //for(int i = 1;i<Na+Ns+1;i++){
      //  for(int j = 1;j<Na+Ns+1;j++){
        //    printf("%d ",map[i][j]);
        //}
        //printf("\n");
    //}
    //map��1-NaΪ�Ȼ����ģ�Na-Na+NsΪ�ӳ���

    //test request
    //printf("һ����%d�������\n",request);
    //for(int i=0;i<request;i++){
      //  printf("��%d���������%d\n",i+1,requestArray[i]);
    //}

    int minDistance[100];
    int path[100] = {0};
    int verticeNum = Na+Ns+1;//ͼ�ж�����

    output(verticeNum,map,requestArray,path,minDistance,Ns,Num);//���
}