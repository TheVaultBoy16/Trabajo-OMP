#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 100000;
double step, pi;

void main()
{
    int i;

    double x, sum = 0.0;

    int n = 4; // num threads


    step = 1.0 / (double)num_steps;

    double t1 = omp_get_wtime();
    
    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    pi = step * sum;

    double t2 = omp_get_wtime();

    printf("Valor de pi: %f\n", pi);
    printf("Tiempo de ejecucion: %f\n", t2-t1);
    
    //return 0;

}

