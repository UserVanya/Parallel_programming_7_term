#include "omp.h"
#include <cassert>
#include <iostream>
#include <cmath>
long double Factorial(int n)
{
  return (n <= 1) ? 1 : Factorial(n - 1) * n;
}
long double GetExpX(size_t pos, long double x)
{
  return std::pow(x, pos) / Factorial(pos);
}
long double GetCosX(size_t pos, long double x)
{
  return (pos % 2 ? -1 : 1) * pow(x, 2 * pos) / Factorial(2* pos); 
}

int main(int argc, char* argv[])
{
  assert(!argv[2]);
  assert(argv[1]);
  size_t n = std::atoi(argv[1]);
  long double sum1 = 0, sum2 = 0;
  double x;
  struct timespec begin, end;
  clock_gettime (CLOCK_REALTIME, &begin);
  std::cout << "Enter x:" << std::endl;
  std::cin >> x;

#pragma parallel for schedule(dynamic) reduction(+, sum1)
  for (size_t i = 0; i < n; i++)
    sum1 += GetExpX(i, x);

#pragma parallel for schedule(dynamic) reduction(+, sum2)
  for (size_t i = 0; i < n; i++)
    sum2 += GetCosX(i, x * x);

  clock_gettime (CLOCK_REALTIME, &end);
  double elapsed = end.tv_sec - begin.tv_sec;
  elapsed
      += (end.tv_nsec - begin.tv_nsec)
             / 1'000'000'000.0;
  std::cout << "Elapsed time: " << elapsed << std::endl;
  std::cout << "e^(" << x << ") * cos("<< x * x << ") = " << sum1 * sum2 << std::endl;
  return 0;
}