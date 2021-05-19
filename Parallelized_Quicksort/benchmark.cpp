#include "sort.h"
#include <stdlib.h>
#include <time.h>
using namespace std;
typedef std::chrono::high_resolution_clock Clock;



void initArray(int *arr, int size) {

  for(int i = 0; i < size; i++) {
    arr[i] = rand() % 1500;
  }
}


int main(int argc, char *argv[]) {

  //Prepare values for benchmark
  srand (time(NULL));
  const int SIZE = 2000;
  int arr[SIZE];
  initArray(arr, SIZE);
  omp_set_num_threads(find_min_exp(2,SIZE));
  
  cout << "Array Initialized with " << to_string(SIZE) << " random values." << endl;
  
  auto t1 = Clock::now();
  #pragma omp parallel default(none) shared(arr,SIZE)
  {
    #pragma omp single nowait
    {quicksort(arr, 0 , SIZE - 1);}
  }

  auto t2 = Clock::now();

  cout << "Parallel Time: " << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() << " nanoseconds" << endl;
  // for (int i = 0; i < SIZE; i++) {
  //     cout << arr[i] << " ";
  // }
  t1 = Clock::now();

  quicksort_not_parallel(arr, 0 , SIZE - 1);

  t2 = Clock::now();

  cout << "Seq Time: " << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() << " nanoseconds" << endl;


  cout << endl;

  return 0;
}
