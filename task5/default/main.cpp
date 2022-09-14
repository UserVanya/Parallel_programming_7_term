#include "omp.h"
#include <cassert>
#include <iostream>
#include <cmath>
long double Factorial(int n)
{
  return (n <= 1) ? 1 : Factorial(n - 1) * n;
}
long double GetElement(size_t pos, long double x)
{
  return std::pow(x, pos) / Factorial(pos);
}
int main(int argc, char* argv[])
{
  assert(!argv[2]);
  assert(argv[1]);
  size_t n = std::atoi(argv[1]);
  long double x, sum = 0;
  std::cout << "Enter x:" << std::endl;
  std::cin >> x;
  struct timespec begin, end;
  clock_gettime (CLOCK_REALTIME, &begin);
#pragma parallel for schedule(dynamic) reduction(+, sum)
  for (size_t i = 0; i < n; i++)
    sum += GetElement(i, x);
  clock_gettime (CLOCK_REALTIME, &end);
  double elapsed = end.tv_sec - begin.tv_sec;
  elapsed
      += (end.tv_nsec - begin.tv_nsec)
             / 1'000'000'000.0;
  std::cout << "Elapsed time: " << elapsed << std::endl;
  std::cout << "e^(" << x << ") = " << sum << std::endl;
  return 0;
}