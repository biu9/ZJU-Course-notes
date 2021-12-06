#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define MinData -1

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
    ElementType  *Elements;
    int Capacity;
    int Size;
};

PriorityQueue Initialize( int MaxElements ); /* details omitted */

void PercolateUp( int p, PriorityQueue H );
void PercolateDown( int p, PriorityQueue H );

void Insert( ElementType X, PriorityQueue H ) 
{
    int p = ++H->Size;
    H->Elements[p] = X;
    PercolateUp( p, H );
}

ElementType DeleteMin( PriorityQueue H ) 
{ 
    ElementType MinElement; 
    MinElement = H->Elements[1];
    H->Elements[1] = H->Elements[H->Size--];
    PercolateDown( 1, H );
    return MinElement; 
}

int main()
{
    int n, i, op, X;
    PriorityQueue H;

    scanf("%d", &n);
    H = Initialize(n);
    for ( i=0; i<n; i++ ) {
        scanf("%d", &op);
        switch( op ) {
        case 1:
            scanf("%d", &X);
            Insert(X, H);
            break;
        case 0:
            printf("%d ", DeleteMin(H));
            break;
        }
    }
    printf("\nInside H:");
    for ( i=1; i<=H->Size; i++ )
        printf(" %d", H->Elements[i]);
    return 0;
}

/* Your function will be put here */
void PercolateUp( int p, PriorityQueue H ){
    int num = p;
    int index;
    while(p > 1){
        if(H->Elements[p] < H->Elements[p/2]){
            index = H->Elements[p];
            H->Elements[p] = H->Elements[p/2];
            H->Elements[p/2] = index;
        }
        p = p/2;
    }
}
void PercolateDown( int p, PriorityQueue H ){
    int index = 1;
    int num_min;
    int flag = 0;
    int change_index;
    while(index < H->Size){
        num_min = H->Elements[index*2];
        if(index*2+1 <= H->Size){
            if(num_min > H->Elements[index*2+1]){
                num_min = H->Elements[index*2+1];
                flag = 1;
            }
        }
        if(H->Elements[index] > num_min){
            change_index = H->Elements[index];
            H->Elements[index] = num_min;
            H->Elements[p*2+flag] = change_index;
        }
        index = index*2 + flag;
    }
}