#include "hw.h"

#define N __X_N
#define blocksize 2
int matA[N*N], matB[N*N],
    matCm[N*N], matCm2[N*N];

int main() {
    input(matA, matB);
    int *matC = matCm, *matC2 = matCm2, n = 1;
    memcpy(matC, matA, sizeof(int[N*N]));
//#pragma omp parallel for schedule(guided, 100)
#pragma omp parallel for num_threads(6)
    for (int i=0;i<N;++i)
        for (int j=0;j<i;++j) {
            int t = matA[i*N+j];
            matA[i*N+j] = matA[j*N+i];
            matA[j*N+i] = t;
        }
//#pragma omp parallel for schedule(guided, 100)
#pragma omp parallel for num_threads(6)
    for (int i=0;i<N;++i)
        for (int j=0;j<i;++j) {
            int t = matB[i*N+j];
            matB[i*N+j] = matB[j*N+i];
            matB[j*N+i] = t;
        }
    for (int k=0;k<n;++k) {
#pragma omp parallel for num_threads(6)
    for (int i=0;i<N*N;++i)
            matA[i] += matB[i];
#pragma omp parallel for num_threads(6)
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j+=4) {
            int sum[4];
            //clear sum，使用sum寄存器减小索引时间
            for(int m=0;m<4;m++){
                sum[m] = 0;
            }

            for (int k=0;k<N;++k){
                int index = matC[i*N+k];//使用index寄存器减少索引时间
                for(int x_inner = 0;x_inner<4;x_inner++){
                    sum[x_inner] += index * matA[(j+x_inner)*N+k];
                }
            }

            //给c矩阵赋值
            for(int fuzhi = 0;fuzhi<4;fuzhi++){
                matC2[i*N+j+fuzhi] = sum[fuzhi];
            }
        }
    int *t = matC; 
    matC = matC2; 
    matC2 = t;
    }
    output(matC, n);
}

