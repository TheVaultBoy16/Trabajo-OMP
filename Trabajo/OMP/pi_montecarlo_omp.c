#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])

{
    unsigned short xi[3] = {1, 2, 3};
    unsigned long long count = 0;
    unsigned long long i;
    unsigned long long samples;
    double x, y;
    samples = 3000000; /*Valor por defecto*/

    int n = 4; // num threads

    	if (argc > 1)
	{
		n = atoi(argv[1]);
	}

    if (argc > 2)
        samples = atoll(argv[2]);

    
    double t1 = omp_get_wtime(); // tiempo inicial


    for (i = 0; i < samples; ++i)
    {
        x = erand48(xi);
        y = erand48(xi);
        if (x * x + y * y <= 1.0)
        {
            ++count;
        }
    }

    double t2 = omp_get_wtime(); // tiempo final

    printf("--------Pi_montecralo_sin_paralelizar--------\n");
    printf("Num_threads: %i\n", n);
    printf("Samples: %llu\n", samples);
    printf("Valor estimado de pi: %.7f\n", 4.0 * count / samples);
	printf("Tiempo de ejecucion: %f\n", t2-t1);
    printf("---------------------------------------------\n");

    return 0;
}

// EJECUCIÓN -> ./pi_montecarlo_omp 200000000