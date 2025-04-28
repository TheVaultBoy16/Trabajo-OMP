# Trabajo-OMP


# COMPILAR Y EJECUTAR :

# OMP:

gcc -g -o0 -fopenmp -o pi_montecarlo_omp_paralelizado  pi_montecarlo_omp_paralelizado.c 

./pi_montecarlo_omp_paralelizado

# MPI:

mpicc -lm -o mpi_montecarlo mpi_montecralo.c 

mpirun -np (num procesos lanzados) mpi_montecarlo