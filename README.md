# Trabajo-OMP


# COMPILAR Y EJECUTAR :

# OMP:

gcc -g -o0 -fopenmp -o pi_montecarlo_omp_paralelizado  pi_montecarlo_omp_paralelizado.c 

./pi_montecarlo_omp_paralelizado

# MPI:

mpicc -O2 mpi_pi.c -o mpi_pi

mpirun -np (num procesos lanzados) mpi_montecarlo