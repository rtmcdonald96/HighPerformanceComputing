//add all elements in an array in parallel
#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
  const int _NUM_THREADS = 8;
  omp_set_num_threads(_NUM_THREADS);
  const int N=32;
  int a[N];
  int tid, nthreads;
  int value,local_odds,total=0;

//Problem #1
//The array is distributed statically between threads.
  #pragma omp parallel for schedule(static,1)
  for (int i=0; i< N; i++)
  {
    a[i] = value;
  }

//Problem #2
//Adds 5*i to array[i] for i=0..32.
  #pragma omp parallel
  {
    #pragma omp for schedule(static,1)
    for (int i=0; i<N; i++)
    {
      //printf("Thread = %d added 5*%d to array a[%d]\n", tid,i,i);
      a[i] = a[i] + 5*i;
    }
  }

//Problem #3
//Cyclic distribution, each thread adds it's local odds
  #pragma omp parallel private(tid, nthreads, local_odds) shared(total)
  {
    local_odds=0;
    tid = omp_get_thread_num();
    //Each thread adds up the total num of local odds
    for (int i = tid; i<N; i += omp_get_num_threads())
    {
      if (a[i]%2 != 0)
      {
        local_odds = local_odds +1;
      }
    }
    //Each thread adds number of local odds to total
    #pragma omp critical
      {
        total += local_odds;
      }

  }
//Master thread prints out total number of odd values
  #pragma omp master
    {
      printf("In the array a[%d] there are %d odd values.\n",N ,total);
    }

return 0;
}
