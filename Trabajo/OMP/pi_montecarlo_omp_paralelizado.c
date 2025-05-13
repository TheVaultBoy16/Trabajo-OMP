#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])

{ // el *argv[] indica un puntero que apunta a un string literal que no puede ser modificado

  // solucion paralelizada
  int p;
  unsigned long long count = 0;
  unsigned long long i;
  unsigned long long samples = 3000000;

  p = omp_get_num_procs(); // obtener numero de procesadores para mostrar por pantalla

  if (argc > 1)
    samples = atoll(argv[1]); // convierte string a long long interger

  double t1 = omp_get_wtime();

#pragma omp parallel reduction(+ : count)
  {
    unsigned short xi[3];
    xi[0] = omp_get_thread_num();
    xi[1] = xi[0] + 1;
    xi[2] = xi[1] + 1;

    double x, y;

#pragma omp for
    for (i = 0; i < samples; ++i)
    {
      x = erand48(xi);
      y = erand48(xi);
      if (x * x + y * y <= 1.0)
      {
        ++count;
      }
    }
  }

  double t2 = omp_get_wtime();

  printf("--------Pi_montecralo_omp_paralelizado--------\n");
  printf("Num_proc: %i\n", p);
  printf("Samples: %llu\n", samples);
  printf("Valor estimado de pi: %.7f\n", 4.0 * count / samples);
  printf("Tiempo de ejecucion: %f\n", t2 - t1);
  printf("----------------------------------------------\n");
  return 0;
}

// EJECUTAR -> OMP_NUM_THREADS=8 ./pi_montecarlo_omp_paralelizado 200000000
