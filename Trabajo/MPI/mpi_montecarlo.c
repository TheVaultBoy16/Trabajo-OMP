#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    unsigned long long i, local_count = 0, total_count = 0;
    unsigned long long samples = 3000000; // Valor por defecto
    double x, y;

    MPI_Init(&argc, &argv);                // Inicializa MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // ID del proceso actual
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Número total de procesos

    if (rank == 0 && argc > 1)
        samples = atoll(argv[1]);

    // Difundir la cantidad total de muestras a todos los procesos
    MPI_Bcast(&samples, 1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);

    // Cada proceso genera samples / size puntos
    unsigned long long local_samples = samples / size;
    unsigned short xi[3] = { (unsigned short)(rank + 1), 2, 3 };

    double t1 = MPI_Wtime();

    for (i = 0; i < local_samples; ++i) {
        x = erand48(xi);
        y = erand48(xi);
        if (x * x + y * y <= 1.0)
            ++local_count;
    }

    // Reducir todos los conteos locales en el proceso raíz
    MPI_Reduce(&local_count, &total_count, 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    double t2 = MPI_Wtime();
    if (rank == 0) {
        double pi = 4.0 * total_count / samples;
        printf("Valor estimado de pi: %.7f\n", pi);
        printf("Tiempo de ejecucion: %f\n", t2 - t1);
    }



    MPI_Finalize();
    return 0;
}


// EJECUTAR -> mpirun -np 4 ./mpi_montecarlo 200000000
// yo en casa no puedo correr mas de 4 procesos porque mi procesador cuenta con 4 cores. Aumentar valor de samples para más precision (cuidado con que se queme la CPU xdd)