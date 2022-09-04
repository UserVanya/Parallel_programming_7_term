#include "omp.h"
#include <iostream>

int
main ()
{
#pragma omp parallel
  {
    std::cout << "Hello, world! Thread num:" << omp_get_thread_num ()
              << " Threads total:" << omp_get_num_threads () << std::endl;
  }
  return 0;
}
