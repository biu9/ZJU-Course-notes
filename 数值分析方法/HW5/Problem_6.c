#include<stdio.h>
#include<math.h>
//use pade rational approximation to count sin(x)[6,6],m=6,n=6

double factorial(int n){
    int i;
    double fact=1;
    for(i=1;i<=n;i++)
        fact*=i;
    return fact;
}
int main(){
    int N = 12;
    int n = 6;
    int m = 6;
    double a[12] = {0,1,0,-1/factorial(3),0,1/factorial(5),0,-1/factorial(7),0,1/factorial(9),0,-1/factorial(11)};
    double b[100][100];
    double q[12] = {0};
    double p[12] = {0};
    q[0] = 1;
    p[0] = a[0];
    for(int i=1;i<=N;i++){
        for(int j=1;j<i;j++){
            b[i][j] = 0;
        }
        if(i <= 6)
            b[i][i] = 1;
        for(int j=i+1;j<=N;j++)
            b[i][j] = 0;
        for(int j=1;j<=i;j++){
            if(j <= 6)
                b[i][6+j] = -a[i-j];
        }
        for(int j=6+i+1;j<=N;j++)
            b[i][j] = 0;
        b[i][N+1] = a[i];
    }
    for(int i=n+1;i<=N-1;i++){
        //let k be the integer with |b[k][i]| = max|b[j][i]|,i<=j<=N
        double max = 0;
        int k;
        for(int j=n+1;j<=N;j++){
            if(fabs(b[j][i]) > max){
                max = fabs(b[j][i]);
                k = j;
            }
        }
        for(int j=i;j<=N+1;j++){
            double temp = b[k][j];
            b[k][j] = b[i][j];
            b[i][j] = temp;
        }
        for(int j=i+1;j<=N;j++){
            b[j][i] /= b[i][i];
            for(int l=i+1;l<=N+1;l++){
                b[j][l] -= b[j][i]*b[i][l];
            }
        }
    }
    for(int i=1;i<=m;i++)
        q[i] = b[N][N+1]/b[N][N];
    for(int i=N-1;i>=n+1;i--){
        q[i] = b[i][N+1];
        for(int j=n+1;j<=N;j++){
            q[i] -= b[i][j]*q[j-n];
        }
        q[i] /= b[i][i];
    }
    for(int i=n;i>=1;i--){
        p[i] = b[i][N+1];
        for(int j=n+1;j<=N;j++){
            p[i] -= b[i][j]*p[j-n];
        }
    }
    //output
    for(int i=1;i<=m;i++){
        printf("q[%d] = %f \n",i,q[i]);
    }
    for(int i=1;i<=n;i++){
        printf("p[%d] = %f \n",i,p[i]);
    }
}