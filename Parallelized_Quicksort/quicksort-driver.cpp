#include "sort.h"
typedef std::chrono::high_resolution_clock Clock;

void test_quicksort() {


    int test[] = { 65, 42, 109, 78, 33, 12, 92, 68, 100, 48, 58, 59, 19, 38, 87, 59 , 67 ,37 ,59 ,65, 91, 34, 67 ,36 ,75 };

    int len = sizeof(test) / sizeof(test[0]);

    omp_set_num_threads(find_min_exp(2,len));

    auto t1 = Clock::now();

    quicksort(test, 0 , len - 1);
    //quicksort_not_parallel(test, 0, len - 1);

    auto t2 = Clock::now();

    std::cout << "time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds \n";

    for (int i = 0; i < len; i++) {
        std::cout << test[i] << "\n";
    }

    return;
}
