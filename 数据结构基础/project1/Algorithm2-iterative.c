#include<stdio.h>
#include<time.h>//Import library functions for time. h
clock_t start,stop;//Declare start and stop
double duration;//declare duraiton

double function(double num,int N){
    double res;//Declare return value
    double temp = num;
    double temp1;//Return temp1 on return
    int i = 1;//Initialization i
    if(N == 0)//if N equals 0 return 1
        return 1;
    else if(N == 1)//if N equals 1 return num
        return num;
    else if(N % 2 == 0){//if N is even
        for(;i<N;){//Start iteration
            temp1 = temp * temp;
            temp = temp1;   
            i *= 2;         
        }
    }
    else{//if N is odd
        for(;i<N-1;){
            temp1 = temp * temp;
            temp = temp1;   
            i *= 2;         
        }
        //Since n is an odd number, multiply it by num
        temp1 *= num;
    }
    //Assign a value to res
    res = temp1;
    return res;
}

int main(){
    double res;
    double num  =1.0001;
    //Repeat K times
    long int K = 0;

    //Use an array to store n to more easily switch between different n
    int mynum[100] = {1000,5000,10000,20000,40000,60000,80000,100000};
    int i = 0;

        start = clock();//Start timing
        while(K < 1000000000){//repeat 1000000000 times to get ticks that is large enough
            res = function(num,mynum[i]);
            K++;
        }  
        stop = clock();//end timing

        duration = (double)((stop-start)/CLK_TCK);//Calculate the time required for one cycle
        printf("N = %d\n",mynum[i]);
        printf("ticks = %.10lf\n",(double)((stop-start)));
        printf("total time = %.10lf\n",duration);
        printf("duration = %.10lf\n",duration/K);
}