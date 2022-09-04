#include "matrix.h"
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
  std::ofstream out ("./results/out" + std::to_string(ms) + ".txt");
  assert (!argv[2]);
  assert (argv[1]);
  Matrix a (ms, ms), b (ms, ms);
  auto numThreads = { 1, 2, 3, 4, 5, 6, 7, 8 };
  out << "ThreadsNumber"
      << "\t"
      << "ElapsedTime" << std::endl;
  for (const auto &n : numThreads)
    {
      size_t runsNum = 5;
      std::vector<double> elapsedVec;
      for (size_t run = 0; run < runsNum; run++)
        {
          struct timespec begin, end;
          omp_set_num_threads (n);
          clock_gettime (CLOCK_REALTIME, &begin);
          a *b;
          clock_gettime (CLOCK_REALTIME, &end);
          double elapsed = end.tv_sec - begin.tv_sec;
          elapsed += (end.tv_nsec - begin.tv_nsec)
                     / 1'000'000'000.0; 
          elapsedVec.push_back (elapsed);
        }
      double elapsedVal
          = std::accumulate (elapsedVec.begin (), elapsedVec.end (), 0.0)
            / elapsedVec.size ();
      out << n << "\t"
          << elapsedVal
          << std::endl;
    }
  return 0;
}
