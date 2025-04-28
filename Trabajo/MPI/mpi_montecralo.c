#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{ // el *argv[] indica un puntero que apunta a un string literal que no puede ser modificado

  // solucion paralelizada

  int rank, size;
  long long int num_samples_por_proc = 1000000;

  unsigned short xi[3] = {1, 2, 3};

  unsigned long long count = 0;
  unsigned long long count_global = 0;
  double x, y;

  /*
  unsigned long long i,a;
  unsigned long long samples;
  samples=3000000; //Valor por defecto
  int n=4;
  */

  // Inicializar MPI

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  MPI_Barrier(MPI_COMM_WORLD);
  double t1 = MPI_Wtime();


  for (long long int i = 0; i < num_samples_por_proc; i++)
  {
    x = erand48(xi) / RAND_MAX;
    y = erand48(xi) / RAND_MAX;

    if (x * x + y * y <= 1.0)
    {
      ++count;
    }
  }


  MPI_Reduce(&count, &count_global, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  double t2 = MPI_Wtime();

  if (rank == 0)
  {
    long long int total_samples = num_samples_por_proc * size;
    double pi_estimado = 4.0 * (double)count_global / (double)total_samples;

    double tiempo_total = t2 - t1;

    printf("Valor estimado de pi:  %.7f\n", pi_estimado);
    printf("Tiempo de ejecucion: %f\n", tiempo_total);
  }

  /*
  if (argc >1)
    samples = atoll(argv[1]); // convierte string a long long interger

  double t1 = omp_get_wtime();

  omp_set_num_threads(n);

  a=omp_get_num_procs();

  #pragma omp parallel for private(x,y)

  for (i = 0; i < samples; ++i) {
    x = erand48(xi);
    y = erand48(xi);
    if (x*x+y*y <= 1.0) {
      ++count;
    }
  }

  double t2 = omp_get_wtime();
  */

  /*

  printf ("Valor estimado de pi:  %.7f\n", 4.0*count/samples);
  printf ("Numero de procesadores: %lld\n",a);
  printf("Tiempo de ejecucion: %f\n", t2-t1);

  */

  MPI_Finalize();

  return 0;
}