#include "omp.h"
#include <cassert>
#include <iostream>
#include <cmath>

long double GetElement(size_t pos)
{
  if (pos == 0)
    return 0;
  else
    return pos % 2 == 0  ? -1.0 / pos : 1.0 / pos;
}
int main(int argc, char* argv[])
{
  assert(!argv[2]);
  assert(argv[1]);
  size_t n = std::atoi(argv[1]);
  long double sum = 0;
  struct timespec begin, end;
  clock_gettime (CLOCK_REALTIME, &begin);
#pragma parallel for schedule(dynamic) reduction(+, sum)
  for (size_t i = 0; i < n; i++)
    sum += GetElement(i);
  clock_gettime (CLOCK_REALTIME, &end);
  double elapsed = end.tv_sec - begin.tv_sec;
  elapsed
      += (end.tv_nsec - begin.tv_nsec)
             / 1'000'000'000.0;
  std::cout << "Elapsed time: " << elapsed << std::endl;
  std::cout << "ln(2) = " << sum << std::endl;
  return 0;
}