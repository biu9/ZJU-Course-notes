#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

/* Your function will be put here */
int visited[100] = {0};
int visitedReverse[100] = {0};
int stack[100];
int ptr = 0;

void dfs(int map[][100],int start,int vertices){
    visited[start] = 1;
    for(int i=0;i<vertices;i++){
        if(map[start][i] != 0 && visited[i] != 1){
            dfs(map,i,vertices);
        }
    }
    stack[ptr++] = start;
}

void dfs2(int mapReverse[][100],int start,int vertices){
    visitedReverse[start] = 1;
    for(int i=0;i<vertices;i++){
        if(mapReverse[start][i] != 0 && visitedReverse[i] != 1){
            dfs2(mapReverse,i,vertices);
        }
    }
    printf("%d ",start);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ){
    int vertices = G->NumOfVertices;
    if(vertices == 1){
        printf("%d \n",G->Array[0]);
        return;
    }
    int edge = G->NumOfEdges;
    int map[100][100];
    int mapReverse[100][100];
    for(int i=0;i<vertices;i++){
        map[i][G->Array[i]->Vert] = 1;
        PtrToVNode tmp;
        tmp = G->Array[i]->Next;
        while(tmp){        
            map[i][tmp->Vert] = 1;
            tmp = tmp->Next;
        }
    }
    for(int i=0;i<vertices;i++){
        if(visited[i] != 1)
            dfs(map,i,vertices);
    }
    for(int i=0;i<vertices;i++){
        for(int j=0;j<vertices;j++){
            mapReverse[i][j] = map[j][i];
        }
    }
    
    for(int i=vertices-1;i>=0;i--){
        if(visitedReverse[stack[i]] != 1){
            dfs2(mapReverse,stack[i],vertices);
        printf("\n");            
        }
    }
}