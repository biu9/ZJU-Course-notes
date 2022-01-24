# Problem 1
### a.
$$
对于x=1.1时，采用Three-Point~~Formulas\\
x_1=x_0+h~~~x_2=x_0+2h\\
f'(x_0)=\frac{1}{h}[-1.5f(x_0)+2f(x_1)-0.5f(x_2)]+\frac{h^2}{3}f^{(3)}(\xi)\\
f'(1.1) =17.769705\\
对于x>1.1时，采用Three-Point~~Midpoint~~Formula\\
f'(x_0) = \frac{1}{2h}[f(x_0+h)-f(x_0-h)]-\frac{h^2}{6}f^{(3)}(\xi)\\
对于x=1.4,采用f'(x_0)=\frac{1}{2h}[f(x_0-2h)-4f(x_0-h)+3f(x_0)]\\
计算结果如下表：
$$

| x    | f(x)     | f'(x)     |
| ---- | -------- | --------- |
| 1.1  | 9.025013 | 17.769705 |
| 1.2  | 11.02318 | 22.193635 |
| 1.3  | 13.46374 | 27.10735  |
| 1.4  | 16.44465 | 21.70365  |

### b.

​	如题a，当x=8.1时，用Three-Point Formulas，当x>8.1时，用Three-Point Midpoint Formula，计算结果如下表：

| x    | f(x)     | f'(x)    |
| ---- | -------- | -------- |
| 8.1  | 16.94410 | 3.09205  |
| 8.3  | 17.56492 | 3.11615  |
| 8.5  | 18.19056 | 3.139975 |
| 8.7  | 18.82091 | 3.363525 |

# Problem 2

$$
M=N(h)+K_1h^2+K_2h^4+K_3h^6...\\
M=N(\frac{h}{3})+K_1\frac{h^2}{3^2}+K_2\frac{h^4}{3^4}+K_3\frac{h^6}{3^6}...\\
M = N(\frac{h}{9})+K_1\frac{h^2}{9^2}+K_2\frac{h^4}{9^4}+K_3\frac{h^6}{9^6}...\\
设x,y解方程以得到O(h^6)\\
\frac{1}{3^2}x+\frac{1}{9^2}y=1\\
\frac{1}{3^4}x+\frac{1}{9^4}y=1\\
x=90,y=-729\\
M_{O^6(h)}=M_h-xM_{\frac{h}{3}}-yM_{\frac{h}{9}}=
$$

# Problem 3

### Trapezoidal rule

##### a.

$$
由于\int_a^bf(x)dx=\frac{h}{2}[f(x_0)+f(x_1)]-\frac{h^3}{12}f''(\xi)\\
\int_{-0.25}^{0.25}(cosx)^2dx=0.25[f(-0.25)+f(0.25)]=0.4999
$$

##### b.

$$
\int_{-0.5}^0xln(x+1)dx=0.25[f(-0.5)+f(0)]=0.0866433
$$

##### c.

$$
\int_{0.75}^{1.3}((sinx)^2-2xsinx+1)dx=\frac{1.3-0.75}{2}[f(0.75)+f(1.3)]=0.5285677628
$$

##### d.

$$
\int_e^{e+1}\frac{1}{xlnx}=0.5[f(e+1)+f(e)]=0.28633417
$$

### Simpson's rule

##### a.

$$
由于\int_{x_0}^{x_2}f(x)dx=\frac{h}{3}[f(x_0)+4f(x_1)+f(x_2)]-\frac{h^5}{90}f^{(4)}(\xi)\\
\int_{-0.25}^{0.25}(cosx)^2dx=\frac{0.25}{3}[f(-0.25)+4f(0)+f(0.25)]=0.4999968269
$$

##### b.

$$
\int_{-0.5}^0xln(x+1)dx=\frac{0.25}{3}[f(-0.5)+4f(-0.25)+f(0)]=0.0528546
$$

##### c.

$$
\int_{0.75}^{1.3}((sinx)^2-2xsinx+1)dx=\frac{0.275}{3}[f(0.75)+4f(1.025)+f(1.3)]=0.5295269385
$$

##### d.

$$
\int_e^{e+1}\frac{1}{xlnx}=\frac{0.5}{3}[f(e)+4f(e+0.5)+f(e+1)]=0.2726704524
$$

# Problem 4
### a.
$$
R_{3,3}=R_{3,2}+\frac{1}{15}(R_{3,2}-R_{2,2})\\
R_{3,2}=R_{3,1}+\frac{1}{3}(R_{3,1}-R_{2,1})\\
R_{2,2}=R_{2,1}+\frac{1}{3}(R_{2,1}-R_{1,1})\\
h=a-b\\
\int_a^bf(x)dx=\frac{h}{2^n}[f(a)+f(b)+2\sum_{j=1}^{n-1}f(x_j)]\\
R_{3,3}=1.452814
$$

```c
#include<stdio.h>
#include<math.h>

double fn(double x){
    return pow(cos(x),2);
}

//romberg intergration to count R_{3,3}
int main(){
    double R33,R32,R31,R22,R21,R11;
    double h;
    double a,b;
    a=-1,b=1;
    //count R11
    h=b-a;
    R11=(h/2)*(fn(a)+fn(b));
    //count R21
    R21=(h/4)*(fn(a)+2*fn(a+h/2)+fn(b));
    //count R31
    R31=(h/8)*(fn(a)+2*(fn(a+h/4)+fn(a+h/2)+fn(a+3*h/4))+fn(b));
    //count R32
    R32=R31+(R31-R21)/3;
    //count R22
    R22=R21+(R21-R11)/3;
    //count R33
    R33=R32+(R32-R22)/15;
    printf("R_{33}=%f\n",R33);
}
```

### b.

$$
类似a，\int_{0.75}^{0.75}xln(x+1)dx=0.327959
$$

```c
#include<stdio.h>
#include<math.h>

double fn(double x){
    return x*log(x+1);
}

//romberg intergration to count R_{3,3}
int main(){
    double R33,R32,R31,R22,R21,R11;
    double h;
    double a,b;
    a=-0.75,b=0.75;
    //count R11
    h=b-a;
    R11=(h/2)*(fn(a)+fn(b));
    //count R21
    R21=(h/4)*(fn(a)+2*fn(a+h/2)+fn(b));
    //count R31
    R31=(h/8)*(fn(a)+2*(fn(a+h/4)+fn(a+h/2)+fn(a+3*h/4))+fn(b));
    //count R32
    R32=R31+(R31-R21)/3;
    //count R22
    R22=R21+(R21-R11)/3;
    //count R33
    R33=R32+(R32-R22)/15;
    printf("R_{33}=%f\n",R33);
}
```

### c.

$$
类似的，\int_{1}^4((sinx)^2-2xsin(x)+1)dx=1.387063
$$

```c
#include<stdio.h>
#include<math.h>

double fn(double x){
    return pow(sin(x),2)-2*x*sin(x)+1;
}

//romberg intergration to count R_{3,3}
int main(){
    double R33,R32,R31,R22,R21,R11;
    double h;
    double a,b;
    a=1,b=4;
    //count R11
    h=b-a;
    R11=(h/2)*(fn(a)+fn(b));
    //count R21
    R21=(h/4)*(fn(a)+2*fn(a+h/2)+fn(b));
    //count R31
    R31=(h/8)*(fn(a)+2*(fn(a+h/4)+fn(a+h/2)+fn(a+3*h/4))+fn(b));
    //count R32
    R32=R31+(R31-R21)/3;
    //count R22
    R22=R21+(R21-R11)/3;
    //count R33
    R33=R32+(R32-R22)/15;
    printf("R_{33}=%f\n",R33);
}
```

### d.

$$
\int_e^{e+1}\frac{1}{xlnx}dx=0.272515
$$

```c
#include<stdio.h>
#include<math.h>

double fn(double x){
    return 1/(log(x)*x);
}

//romberg intergration to count R_{3,3}
int main(){
    double R33,R32,R31,R22,R21,R11;
    double h;
    double a,b;
    a=exp(1),b=exp(1)+1;
    //count R11
    h=b-a;
    R11=(h/2)*(fn(a)+fn(b));
    //count R21
    R21=(h/4)*(fn(a)+2*fn(a+h/2)+fn(b));
    //count R31
    R31=(h/8)*(fn(a)+2*(fn(a+h/4)+fn(a+h/2)+fn(a+3*h/4))+fn(b));
    //count R32
    R32=R31+(R31-R21)/3;
    //count R22
    R22=R21+(R21-R11)/3;
    //count R33
    R33=R32+(R32-R22)/15;
    printf("R_{33}=%f\n",R33);
}
```

# Problem 5

### a.

$$
由于w_0=\alpha\\
w_{i+1}=w_i+hf(t_i,w_i)\\
n=\frac{2-1}{0.1}=10\\
w_0=y(1)=1\\
t_{i+1} = t_i+h\\
t_0=1\\
计算得到：y(2)=1.170652
$$

```c
#include<stdio.h>
#include<math.h>

//use Eluer's method to approximate the solution for each of the following initial conditions value

double fn(double t,double w){
    return w/t-pow(w/t,2);
}

int main(){
    double w=1;
    double n=10;
    double h=0.1;
    double t=1;
    for(int i=0;i<n;i++){
        w=w+h*fn(t,w);
        t=t+h;
    }
    printf("w=%f\n",w);
}
```

### b.

$$
类似a题目
\\w_0=0\\
t_0=1\\
n=10\\
h=0.2\\
计算得：y(3)=4.514277
$$

```c
#include<stdio.h>
#include<math.h>

//use Eluer's method to approximate the solution for each of the following initial conditions value

double fn(double t,double w){
    return 1+w/t+pow(w/t,2);
}

int main(){
    double w=0;
    double n=10;
    double h=0.2;
    double t=1;
    for(int i=0;i<n;i++){
        w=w+h*fn(t,w);
        t=t+h;
    }
    printf("w=%f\n",w);
}
```

# Problem 6

$$
[6,6]_{sinx}=\frac{(x-\frac{x^3}{3!}+\frac{x^5}{5!}-\frac{x^7}{7!})(1+q_1x+q_2x^2+q_3x^3+q_4x^4+q_5x^5+q_6x^6)}{p_0+p_1x+p_2x^2+p_3x^3+p_4x^4+p_5x^5+p_6x^6}\\
\sum_{i=0}^ka_iq_{k-i} = p_k
$$

使用如下代码进行计算：

```c
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
```

没有得到正确结果

# Problem 7

由于：

| i    | x    | y    |
| ---- | ---- | ---- |
| 1    | 0    | 6    |
| 2    | 2    | 8    |
| 3    | 4    | 14   |
| 4    | 5    | 20   |

$$
a_0=\frac{\sum x_i^2\sum y_i-\sum x_iy_i\sum x_i}{m(\sum x_i^2)-(\sum x_i)^2}\\
a_1=\frac{m\sum x_iy_i-\sum x_i\sum y_i}{m(\sum x_i^2)-(\sum x_i)^2}\\
P(x_i) = a_1x_i+a_0\\
E=\sum[y_i-P(x_i)]^2\\
计算得到：\\
P(x_i)=2.711864407x+4.542372881\\
E=11.525424
$$

