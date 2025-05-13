#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {

	//solucion paralelizada
	
	int i,p;
	double x, pi, sum = 0.0;
	long numSteps = 100000;
	int n=4;

    p = omp_get_num_procs(); //obtener numero de procesadores para mostrar por pantalla


	if (argc >1){ // numero de argumentos que le paso (./ threads trapecios) son 3 argumentos (0,1,2)
		n=atoi(argv[1]); // convertir string (char) en enteros (int) (impar), convierto a int el numero de threads
	}

	if (argc >2){ // numero de argumentos que le paso
		numSteps=atol(argv[2]); // convertir string (char) en enteros (long) (par), convierto a long el numero de trapecios pasados como argumento
	}

	double step = 1.0 / (double)numSteps;

	omp_set_num_threads(n); // importado desde omp.h

	double t1 = omp_get_wtime(); // se mide el tiempo del bucle solo y abajo se para de medir el tiempo, se hace la difrencia para el tiempo total
	
	//distribuye el numero de iteraciones del for entre el numero maximo de threads existentes 
	#pragma omp parallel for private(i,x) reduction(+:sum) // se puede hacer sin el reduction y con el critical debajo, critical cuando hay una region paralela rompe el paralelismo para evitar condicion de carrera, reparte de uno en uno
	// las variables de dentro del private indican que cada hilo tendrá una copia local y la usará como variable temporal
	for (i=0; i<numSteps; ++i) {
		x = (i+0.5)*step; // step -> trapecios
		double aux = 4.0/(1.0+x*x); // cond de carrera ? (con el sum ahi metido?)
		
		// solo un hilo a la vez
		//#pragma omp critical 

		sum+=aux;

		}
	pi = step * sum;
	
	double t2 = omp_get_wtime();
	
	printf("Valor de pi: %f\n", pi);
	printf("Tiempo de ejecucion: %f\n", t2-t1);
	return 0;
}

