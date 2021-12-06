#include<stdio.h>
#include<time.h>//Import library functions for time. h
clock_t start,stop;//Declare start and stop
double duration;//declare duraiton

double function(double num,int N){
    if(N == 0)
        return 1;
    if(N == 1)
        return num;
    if(N % 2 == 0)
        return function(num*num,N/2);//Start recursion
    else
        return function(num * num,N/2) * num;
}

int main(){
    double num  =1.0001;
    //Repeat K times
    long int K = 0;
    
    //Use an array to store n to more easily switch between different n
    int mynum[100] = {1000,5000,10000,20000,40000,60000,80000,100000};
    int i = 0;

    start = clock();//Start timing
    while(K < 1000000000){
        function(num,mynum[i]);
        K++;
    }  
    stop = clock();//stop timing

    duration = (double)((stop-start)/CLK_TCK);//Calculate the time required for one cycle
    printf("N = %d\n",mynum[i]);
    printf("ticks = %.10lf\n",(double)((stop-start)));
    printf("total time = %.10lf\n",duration);
    printf("duration = %.10lf\n",duration/K);
}