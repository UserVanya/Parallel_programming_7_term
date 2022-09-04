#include "omp.h"
#include <iostream>

int
main ()
{
  int n = omp_get_max_threads() - 1;
#pragma omp parallel shared(n)
  {
    while(n != omp_get_thread_num()) {}
    std::cout << "Hello, world! Thread num:" << omp_get_thread_num ()
              << " Threads total:" << omp_get_num_threads () << std::endl;
    n--;
  }
  return 0;
}
