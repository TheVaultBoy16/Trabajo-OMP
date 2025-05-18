# Trabajo-OMP


# COMPILAR Y EJECUTAR :

# OMP:

gcc -g -o0 -fopenmp -o pi_montecarlo_omp_paralelizado  pi_montecarlo_omp_paralelizado.c 

OMP_NUM_THREADS=8 ./pi_montecarlo_omp_paralelizado 200000000

./pi_omp_paralelizado 4  100000   //(hilos y numSteps)

# MPI:

mpicc -O2 mpi_pi.c -o mpi_pi

mpirun -np (num procesos lanzados) mpi_montecarlo (numSTeps o numSamples)