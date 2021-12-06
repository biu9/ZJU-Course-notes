#include<stdio.h>
#include<math.h>

int N;//节点个数
int buildedTree[20000];

void sort(int* array,int Number){
    int index;
    if(Number > 1)
    for(int i = 0;i<Number;i++){
        for(int j = 0;j<Number-1;j++){
            if(array[j]>array[j+1]){
                index = array[j];
                array[j] = array[j+1];
                array[j+1] = index;
            }
        }
    }
}

void buildTree(int* Tree,int index,int start,int end){
    if(start > end) return;
    for(int i = 0;i<11;i++){
        if(pow(2,i) <= (end-start+1) && pow(2,i+1) > (end-start+1)){
            N = i;
            break;
        }
    }
    int treeIndex;
    if((end-start+1)-pow(2,N) < pow(2,N-1)){
        treeIndex = end+1-pow(2,N-1);//(end-start+1)-pow(2,N)+pow(2,N-1)+start
    }
    else{
        treeIndex = pow(2,N)+start-1;
    }

    //int treeIndex = (end+1)-pow(2,N-1);
    buildedTree[index] = Tree[treeIndex];

    buildTree(Tree,index*2+1,start,treeIndex-1);
    buildTree(Tree,index*2+2,treeIndex+1,end);

}

int main(){
    int Number;
    scanf("%d",&Number);
    int Tree[1000];
    for(int i = 0;i<Number;i++)
        scanf("%d",&Tree[i]);
    for(int i = 0;i<20000;i++)
        buildedTree[i] = -1;
    
    sort(Tree,Number);
    buildTree(Tree,0,0,Number-1);
    for(int i = 0;i<20000;i++){
        if(i == 0)
            printf("%d",buildedTree[i]);
        else if(buildedTree[i] != -1)
            printf(" %d",buildedTree[i]);
    }
}