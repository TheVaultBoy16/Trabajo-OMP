#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NUM_STEPS 100000000

int main(int argc, char *argv[]) {
    int rank, size, i;
    double x, sum = 0.0, pi = 0.0;
    double step = 1.0 / (double)NUM_STEPS;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // ID del proceso actual
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Número total de procesos

    double t1 = MPI_Wtime();

    // Cada proceso calcula su porción del sumatorio
    for (i = rank; i < NUM_STEPS; i += size) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    // Sumar todos los resultados parciales en el proceso raíz
    MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    double t2 = MPI_Wtime();

    if (rank == 0) {
        pi *= step;
        printf("Valor estimado de pi: %.7f\n", pi);
        printf("Tiempo de ejecucion: %f\n", t2 - t1);
    }

    MPI_Finalize();
    return 0;
}

// EJECUTAR -> mpirun -np 4 ./mpi_pi (ya del carajo con ese numero de muestras)