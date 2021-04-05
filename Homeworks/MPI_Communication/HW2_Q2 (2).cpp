#include "mpi.h"
#include <iostream>

int main(int argc, char* argv[])
{
    int rank,size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank( MPI_COMM_WORLD, &rank);
    MPI_Comm_size( MPI_COMM_WORLD, &size);
    std::cout << "I am " << rank << " of " << size << std::endl;
    double start_time, end_time;

    int value = -10;
    std::cout << "Process " << rank << " has value " << value << std::endl;
    start_time = MPI_Wtime();
    if(rank != 0)
    {
        MPI_Recv(&value, 1, MPI_INT,(rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Process " << rank << " received value " << value << " to process " << (rank -1)%size << std::endl;
    }
    else
    {
        value = -1;
    }

    MPI_Send(&value, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        MPI_Recv(&value, 1, MPI_INT, size -1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Process " << rank << " received value " << value << " from process " << size -1 << std::endl;
    }
    end_time = MPI_Wtime();
    if (rank == 0)
    {
    printf("Total execution time: %f\n", end_time-start_time);
    }
    MPI_Finalize();
    return 0;
}
