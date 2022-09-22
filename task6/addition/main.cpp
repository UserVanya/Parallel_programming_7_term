#include "omp.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
bool
isPrime (size_t val)
{
  if (val == 1 || val == 2)
    return true;
  // Doesn't need to check every even number
  if (val == 0 || val % 2 == 0)
    return false;
  // Let sqrt(val) = s then we check all values before s because of symmetry
  // checked * (s + i) = (s + i) * checked
  for (int i = 3; i <= sqrt (val); i += 2)
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
  elapsed += (end.tv_nsec - begin.tv_nsec) / 1'000'000'000.0; std::cout
             << "Elapsed time: " << elapsed << std::endl;
  std::cout << "Number of prime numbers: " << primeNumber << std::endl;
  return 0;
}