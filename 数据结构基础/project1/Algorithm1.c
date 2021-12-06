#include<stdio.h>
#include<time.h>//Import library functions for time. h
clock_t start,stop;//Declare start and stop
double duration;//declare duraiton

double function(double num,int N){
    double res = 1;//Declare return value
    if(N == 0)
        return 1;
    else{
        //Use a for loop to calculate the result
        for(int i = 0;i<N;i++){
            res *= num;
        }
        //return result
        return res;
    }
}

int main(){
    double num  =1.0001;
    double res;
    //Repeat K times
    long int K = 0;
    
    //Use an array to store n to more easily switch between different n
    int mynum[100] = {1000,5000,10000,20000,40000,60000,80000,100000};
    int i = 7;
        
        start = clock();//Start timing
        while(K < 1000000){//repeat 100000 times to get ticks that is large enough
            res = function(num,mynum[i]);
            K++;
        }  
        stop = clock();//stop timing

        duration = (double)((stop-start)/CLK_TCK);//Calculate the time required for one cycle
        printf("N = %d\n",mynum[i]);
        printf("ticks = %.10lf\n",(double)((stop-start)));
        printf("total time = %.10lf\n",duration);
        printf("duration = %.10lf\n",duration/K);
}