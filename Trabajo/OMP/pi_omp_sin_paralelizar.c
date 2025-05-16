#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 100000;
double step, pi;

int main(int argc, char *argv[])
{
    int i;

    double x, sum = 0.0;

    int n = 4; // num threads

    	if (argc > 1)
	{
		n = atoi(argv[1]);
	}

    	if (argc > 2)
	{
		num_steps = atoll(argv[2]);
	}

    step = 1.0 / (double)num_steps;

    double t1 = omp_get_wtime();
    
    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    pi = step * sum;

    double t2 = omp_get_wtime();

    printf("--------Pi sin paralelizar--------\n");
    printf("Num_threads: %i\n", n);
    printf("Num_steps: %li\n", num_steps);
    printf("Valor de pi: %f\n", pi);
    printf("Tiempo de ejecucion: %f\n", t2-t1);
    printf("----------------------------------\n");
    
    return 0;

}

