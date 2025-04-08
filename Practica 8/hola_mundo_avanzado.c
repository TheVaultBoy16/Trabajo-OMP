#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {

  int mi_rango, tamanno;
  char nombre_proc[MPI_MAX_PROCESSOR_NAME];
  int tam_nombre_proc;

  MPI_Init(&argc, &argv);		// Inicializa MPI
  
  MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango); // identificador
  
  MPI_Comm_size(MPI_COMM_WORLD, &tamanno); // numero procesos totales

  MPI_Get_processor_name(nombre_proc, &tam_nombre_proc);

  if (mi_rango == 0){
    printf("Soy el proceso %i de %i corriendo en %s: !Hola mundo!\n",mi_rango,tamanno,nombre_proc);
  }
  else{
    printf("Yo soy el proceso %i de %i, corriendo en %s: !Hola mundo!\n",mi_rango,tamanno,nombre_proc);
  }

  MPI_Finalize();
  return(0);
}
