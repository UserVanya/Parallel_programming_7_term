#include "omp.h"
#include <cassert>
#include <cmath>
#include <iostream>
bool
isPrime (size_t val)
{
  if (val == 0) return false;
  for (int i = 2; i < val; i++)
    {
      if (val % i == 0)
        return false;
    }
  return true;
}
int
main (int argc, char *argv[])
{
  assert (!argv[2]);
  assert (argv[1]);
  size_t n = std::atoi (argv[1]);
  struct timespec begin, end;
  size_t primeNumber = 0;
  clock_gettime (CLOCK_REALTIME, &begin);
#pragma parallel for schedule(dynamic) reduction(+, primeNumber)
  for (size_t i = 0; i <= n; i++)
    primeNumber += isPrime (i);
  clock_gettime (CLOCK_REALTIME, &end);
  double elapsed = end.tv_sec - begin.tv_sec;
  elapsed += (end.tv_nsec - begin.tv_nsec) / 1'000'000'000.0;
  std::cout << "Elapsed time: " << elapsed << std::endl;
  std::cout << "Number of prime numbers: " << primeNumber << std::endl; 
  return 0;
}