//estimation of pi 

#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<math.h>


#define num_steps 1000000 //infinity assumption


void main(){

    //serial
    
    float pi=0;
    double start = omp_get_wtime();

    for(int k=0;k<num_steps;k++)
    {
        pi += pow(-1,k)/(2*k+1);
    }

    pi = 4* pi;

    double end = omp_get_wtime();
    double time = end-start;

    printf("value of pi in serial : %f with time : %f\n",pi,time);

    //parallel

    pi = 0;
    start = omp_get_wtime();

    float thread[8];
    #pragma omp parallel for num_threads(8)

    for(int k=0;k<num_steps;k++)
    {
        int t = omp_get_thread_num();
        thread[t] += pow(-1,k)/(2*k+1);
    }

    for(int i=0;i<8;i++)
    {
        pi += thread[i];
    }

    pi = 4 * pi;

    end = omp_get_wtime();
    time = end-start;

    printf("value of pi in parallel : %f with time : %f\n",pi,time);

     
}
