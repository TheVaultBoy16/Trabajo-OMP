#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

//#define NUM_STEPS 100000000

int main(int argc, char *argv[]) {
    int rank, size, i;
    unsigned long long NUM_STEPS = 3000000;
    double x, sum = 0.0, pi = 0.0;

    if (rank == 0 && argc > 1)
        NUM_STEPS = atoll(argv[1]);


    double step = 1.0 / (double)NUM_STEPS;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    double t1 = MPI_Wtime();

    
    for (i = rank; i < NUM_STEPS; i += size) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    
    MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    double t2 = MPI_Wtime();

    if (rank == 0) {
        pi *= step;
        printf("--------Pi_mpi--------\n");
        printf("Num_steps: %llu\n", NUM_STEPS);
        printf("Valor estimado de pi: %.7f\n", pi);
        printf("Tiempo de ejecucion: %f\n", t2 - t1);
        printf("----------------------\n");
    }

    MPI_Finalize();
    return 0;
}

// EJECUTAR -> mpirun -np 4 ./mpi_pi (ya del carajo con ese numero de muestras)