/*
 * Algoritmo serie de Monte Carlo para estimar el valor de pi
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc, char *argv[]) { // el *argv[] indica un puntero que apunta a un string literal que no puede ser modificado
  // solucion sin paralelizar
  unsigned short xi[3] = { 1, 2, 3 };
  unsigned long long count = 0;
  unsigned long long i;
  unsigned long long samples;
  double x, y;
  samples=3000000; /*Valor por defecto*/

  if (argc >1)
    samples = atoll(argv[1]); // convierte string a long long interger
    
  double t1 = omp_get_wtime();
  for (i = 0; i < samples; ++i) {
    x = erand48(xi);
    y = erand48(xi);
    if (x*x+y*y <= 1.0) {
      ++count;
    }
  }

  double t2 = omp_get_wtime();

  printf ("Valor estimado de pi:  %.7f\n", 4.0*count/samples);
  printf("Tiempo de ejecucion: %f\n", t2-t1);
  return 0;
}
