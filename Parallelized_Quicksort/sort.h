#pragma once
#include <iostream>
#include <omp.h>
#include <chrono>
#include <math.h>


/**
 * @brief Used to calcuate number of threads for array distribution
 * @param base The base number of the exponent
 * @param target The target value
 * @return The minimum exponent
*/
int find_min_exp(int base, int target);


/**
 * @brief The quick sort algorithm using OpenMP
 * @param arr An array to be sorted
 * @param low Left side index
 * @param high Right side index
*/
void quicksort(int arr[], int low, int high);

/**
 * @brief Hoare’s partition algorithm
 * @param arr an array to partition
 * @param low left side index
 * @param high right side index
 * @return index of middle of the partitioned array
*/
int partition(int arr[], int low, int high);

/**
 * @brief The sequential quick sort algorithm
 * @param arr An array to be sorted
 * @param low Left side index
 * @param high Right side index
*/
void quicksort_not_parallel(int arr[], int low, int high);
