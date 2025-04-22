#include <stdio.h>
#include <math.h>
#include <mpi.h>

// ejercicio de trabajo

float f(float x);
double Trap(double left_endpt, double right_endpt, int trap_count, double base_len);
int main(int argc, char** argv) {
	int my_rank, comm_sz, local_n;
	int         n = 10000; // NUMERO DE TRAPECIOS
	double       a = -1.0;  // EXTREMO IZQUIERDO
	double      b = 1.0;   // EXTREMO DERECHO
	double h, local_a, local_b;
	double local_int, total_int;
	int source;
	MPI_Init(&argc, &argv);		
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	double t1= MPI_Wtime();
	//...
	h = (b-a)/n; /* h es igual para todos los procesos */
	local_n = n/comm_sz; /* nï¿½mero de trapezoides por proceso */
	local_a = a + my_rank*local_n*h;
	local_b = local_a + local_n*h;
	local_int = Trap(local_a, local_b, local_n, h); /* ver mï¿½s adelante */	
	MPI_Reduce(&local_int,&total_int,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD); // añadido MPI_Reduce
	//...
	double t2= MPI_Wtime();
	if(my_rank == 0) {
		printf("With n = %d trapezoids , our estimate \n", n);
		printf("of the integral from %f to %f = %.15e\n" , a, b, total_int);
		printf("PI = %f\n", 2 * total_int);
		printf("P2: Execution Time: %f\n", t2-t1);
	}
	MPI_Finalize();
		return 0;
}


float f(float x) {
	float return_val;
	return_val = sqrt( 1 - x*x );
	return return_val;
}
	
	
double Trap(double left_endpt, double right_endpt, int trap_count, double base_len) {
	double estimate, x;
	int i;
	estimate = (f(left_endpt) + f(right_endpt))/2.0;
	for (i = 1; i <= trap_count -1; i++) {
		x = left_endpt + i* base_len;
		estimate += f(x);
	}
	estimate = estimate*base_len;
	return estimate;
}
