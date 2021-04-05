//=============================================================================
// CPSC 479-01 Project 1
// Ryan McDonald - rtmcdonald96@csu.fullerton.edu
//=============================================================================

#include "mpi.h"
#include <iostream>
#include <cmath>
#include <string>

int main(int argc, char* argv[])
{
//=============================================================================
// MPI Initialization
//=============================================================================

    int rank,size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank( MPI_COMM_WORLD, &rank);
    MPI_Comm_size( MPI_COMM_WORLD, &size);

//=============================================================================
// Variables used to solve problem
//=============================================================================

    int random_num, is_even, high_even, high_odd, my_value;

//=============================================================================
// Random Number Generation with concatenation
//=============================================================================

    srand(time(NULL) + rank);
    random_num = rand() % 100;
    if (random_num < 0)
    {
      random_num = std::abs(random_num);
    }

    if (random_num < 10)
    {
      random_num  = random_num + 10;
    }

    if (random_num > 100)
    {
      random_num = random_num % 100;
    }
    my_value = std::stoi(std::to_string(1)+std::to_string(random_num)+std::to_string(rank));
    //Cout statement is commented out to remove clutter from terminal
    //Can remove comment in order to see value that each process has
    //std::cout << "Process " << rank << " has value " << my_value << std::endl;

//=============================================================================
// Flag for even and odd
//=============================================================================

    if (my_value % 2 == 0)
    {
      is_even = 1;
    }
    else
    {
      is_even = 0;
    }

//=============================================================================
// Declare highest even and odd storage variables
//=============================================================================

    high_even = 0;
    high_odd = 0;

//=============================================================================
// Process receives highest even and odd values from previous process
//=============================================================================

    if(rank != 0)
    {
        MPI_Recv(&high_even, 1, MPI_INT,(rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&high_odd, 1, MPI_INT,(rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        //Cout statements are commented out to remove clutter from terminal
        //Can remove comment in order to see the value that each process is receiving from previous process
        //std::cout << "Process " << rank << " received even value " << high_even << " from process " << (rank -1)%size << std::endl;
        //std::cout << "Process " << rank << " received odd value " << high_odd << " from process " << (rank -1)%size << std::endl;
    }

//=============================================================================
// Depending on process value, comparison is done based on highest even or odd
//=============================================================================

    if (is_even == 1)
    {
      if (high_even < my_value)
      {
      high_even = my_value;
      }
    }
    else if (is_even == 0)
    {
      if (high_odd < my_value)
      {
      high_odd = my_value;
      }
    }
      MPI_Send(&high_even, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
      MPI_Send(&high_odd, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
//=============================================================================
// Highest even and odd values received from process size-1
//=============================================================================

   if (rank == 0)
    {
    MPI_Recv(&high_even, 1, MPI_INT,size -1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&high_odd, 1, MPI_INT,size -1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //Cout statements are commented out to remove clutter from terminal
    //Can remove comment in order to see the highest values at end of ring
    //std::cout << "Process " << rank << " received even value " << high_even << " from process " << size -1 << std::endl;
    //std::cout << "Process " << rank << " received odd value " << high_odd << " from process " << size -1 << std::endl;
    }

//=============================================================================
// President and vice president are declared
//=============================================================================

    //Broadcast highest even and odd values to each process
    MPI_Bcast(&high_even,1,MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&high_odd, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //If process value is equal to highest even or odd it is declared pres/vp
    if (my_value == high_odd)
    {
        std::cout << "Process " << rank << " is the president(largest odd)." << std::endl;
    }
    if (my_value == high_even)
    {
        std::cout << "Process " << rank << " is the vice-president(largest even)." << std::endl;
    }

    MPI_Finalize();
    return 0;
}
