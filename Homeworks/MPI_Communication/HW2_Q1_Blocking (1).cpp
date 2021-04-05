#include <stdio.h>
#include <mpi.h>

int main( int argc, char *argv[] )
{
  int rank, size;
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  //Variables to keep track of time
  double start_time, end_time, round_time;
  //Value of double originally starts at 0. Double to be sent between prrocesses
  double value = 0;

  start_time = MPI_Wtime();
  //Process rank 0 sends 10.1 to process rank 1
  if (rank == 0) {

    //Set value to 10.1 to send to process 1
    value = 10.1;
    //Set starting time right before value is sent
    MPI_Send(&value, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);

  //Process rank 1 recieves 10.1 from process rank 0
  } else if (rank == 1) {

    MPI_Recv(&value, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
  end_time = MPI_Wtime();
  //end_time = MPI_Wtime();

  //Round trip sending 10.1 from rank 1 back to rank 0
  //Process rank 1 sends 10.1 to process rank 0
  if (rank == 1) {
    //Set value to 10.1 to send to process 0
    MPI_Send(&value, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  //Process rank 0 recieves 10.1 from process rank 1
} else if (rank == 0) {
    MPI_Recv(&value, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //Set round trip ending time right after value is received.
  }
  round_time = MPI_Wtime();
  if(rank == 1)
  {
  printf("Total execution time for single send: %f\n", end_time-start_time);
  }
  if(rank == 0)
  {
  printf("Total execution time for round trip: %f\n", round_time-start_time);
  }
  MPI_Finalize();

  return 0; ;
}
