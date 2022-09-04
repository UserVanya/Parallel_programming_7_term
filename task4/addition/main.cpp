#include "experiment/matrix.h"
#include "omp.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <time.h>
#include <vector>

int
main (int argc, char *argv[])
{
  size_t ms = std::atoi (argv[1]);
  assert (!argv[2]);
  assert (argv[1]);
  Matrix a (ms, ms), b (ms, ms);
  // For measuring elapsed time
  struct timespec begin, end;
  size_t opsNum = ms * ms * ms;
  size_t freq = 1e9;
  std::cout << "Minimum estimated time: "
            << 1.0 * opsNum / freq / omp_get_max_threads () << std::endl;
  std::cout << "Matrix multiplication started..." << std::endl;
  clock_gettime (CLOCK_REALTIME, &begin);
  a *b;
  clock_gettime (CLOCK_REALTIME, &end);
  std::cout << "Done!" << std::endl;
  double elapsed = end.tv_sec - begin.tv_sec;
  elapsed += (end.tv_nsec - begin.tv_nsec) / 1'000'000'000.0; 
  std::cout << "Elapsed time: " << elapsed << std::endl;
  return 0;
}
