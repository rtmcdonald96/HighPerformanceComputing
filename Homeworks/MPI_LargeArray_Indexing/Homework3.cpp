#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <iostream>
int main(int argc, char* argv[])
{
    int rank, size,random_num, index_part_two;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    srand(time(NULL) + rank);
    random_num = rand() % 100;
    //Make sure random number genereated is odd
    if (random_num % 2 == 0) {
      random_num = random_num + 1;
    }
    MPI_Scan(&random_num, &index_part_two, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("Process %d will receive the array portion between index %d - %d\n",
          rank,(index_part_two - random_num + 1),index_part_two);
    MPI_Finalize();
    return 0;
}
