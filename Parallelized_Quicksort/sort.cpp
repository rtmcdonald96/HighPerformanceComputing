#include "sort.h"


int find_min_exp(int base, int target) {
    int i = 0;
    while (pow(base, i) < target) { i++; }
    return i;
}

int partition(int arr[], int low, int high) {
  int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quicksort(int arr[], int low, int high) {
    //TODO: Implement
    if (low < high)
    {
        int mid = partition(arr, low, high);

        //Using OpenMP Tasks.
        #pragma omp task shared(arr) firstprivate(low, mid)
        {
            quicksort(arr, low, mid - 1);
        }
        #pragma omp task shared(arr) firstprivate(high, mid)
        {
            quicksort(arr, mid + 1, high);
        }

        //Wait for tasks to finish

        #pragma omp taskwait


    }
}

void quicksort_not_parallel(int arr[], int low, int high) {
    if (low < high)
    {
        int mid = partition(arr, low, high);
        quicksort_not_parallel(arr, low, mid - 1);
        quicksort_not_parallel(arr, mid + 1, high);
    }
}
