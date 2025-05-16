#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{

	// solucion paralelizada

	int i, p;
	double x, pi, sum = 0.0;
	unsigned long long numSteps = 100000;
	int n = 4;

	p = omp_get_num_procs();

	if (argc > 1)
	{
		n = atoi(argv[1]);
	}

	if (argc > 2)
	{
		numSteps = atoll(argv[2]);
	}

	double step = 1.0 / (double)numSteps;

	omp_set_num_threads(n);

	double t1 = omp_get_wtime();

#pragma omp parallel for private(i, x) reduction(+ : sum)

	for (i = 0; i < numSteps; ++i)
	{
		x = (i + 0.5) * step;
		double aux = 4.0 / (1.0 + x * x);
		sum += aux;
	}
	pi = step * sum;

	double t2 = omp_get_wtime();

	printf("--------Pi_omp_paralelizado--------\n");
	printf("Num_threads: %i\n", n);
	printf("Num_steps: %llu\n", numSteps);
	printf("Valor de pi: %f\n", pi);
	printf("Tiempo de ejecucion: %f\n", t2 - t1);
	printf("-----------------------------------\n");

	return 0;
}

// EJECUCIÓN -> ./pi_omp_paralelizado 4  100000   (hilos y numSteps)
