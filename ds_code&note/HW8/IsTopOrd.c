#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 1 to MaxVertexNum */

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */

bool IsTopSeq( LGraph Graph, Vertex Seq[] );

int main()
{
    int i, j, N;
    Vertex Seq[MaxVertexNum];
    LGraph G = ReadG();
    scanf("%d", &N);
    for (i=0; i<N; i++) {
        for (j=0; j<G->Nv; j++)
            scanf("%d", &Seq[j]);
        if ( IsTopSeq(G, Seq)==true ) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}

/* Your function will be put here */

bool IsTopSeq( LGraph Graph, Vertex Seq[] ){
    int flag = 1;
    for(int i = 0;i<(Graph->Nv)-1;i++){
        PtrToAdjVNode index = Graph->G[Seq[i+1]-1].FirstEdge;
        while(index != NULL){
            if(index->AdjV+1 == Seq[i]){
                //printf("i = %d, index->AdjV = %d\n",i,index->AdjV);
                flag = 0;
                break;
            }
            PtrToAdjVNode next = index->Next;
            index = next;
        }
        if(flag == 0)
            break;
    }
    if(flag == 1)
        return true;
    else
        return false;
}