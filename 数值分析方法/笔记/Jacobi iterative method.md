# Jacobi iterative method

	### definition

​	the Jacobi iterative method is obtained by solving the ith equation in AX=b for $x_i$ to obtain(provided $a_{ii}$≠0)：
$$
x_i=\sum_{j=1}^n(-\frac{a_{ij}}{a{ii}})+\frac{b_i}{a_{ii}}~~~~~~(j≠i)\\
x_i^{(k)} = \frac{1}{a_{ii}}[\sum_{j=1}^n(-a_{ij}x_{j}^{(k-1)})+b_i]
$$

### code

```c
#include<stdio.h>

int main(){
    double x[100][100] = {
        {4,1,-1,5},
        {-1,3,1,-4},
        {2,2,5,1},
    };
    double x1,x2,x3;    
    double xTmp1,xTmp2,xTmp3;
    double sumTmp = 0;
    x1 = x2 = x3 = 0;
    int i=0;
    while(++i<10){
        xTmp1 = (-(x[0][1]*x2+x[0][2]*x3)+x[0][3])/x[0][0];
        xTmp2 = (-(x[1][0]*x1+x[1][2]*x3)+x[1][3])/x[1][1];
        xTmp3 = (-(x[2][0]*x1+x[2][1]*x2)+x[2][3])/x[2][2];
        x1 = xTmp1;
        x2 = xTmp2;
        x3 = xTmp3;
        printf("第%d次迭代:x1=%f,x2=%f,x3=%f\n",i,x1,x2,x3);
    }
}
```

