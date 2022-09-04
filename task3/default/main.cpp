#include "omp.h"
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

double
get_val (size_t prev, size_t cur, size_t next)
{
  return prev * cur * next / 3;
}
int
main (int argc, char *argv[])
{
  size_t n = 100'000; n = 20;
  std::vector<size_t> a (n), b (n, 0);
  // std::cout << std::numeric_limits<double>::max() << std::endl;
  // gives 1.79769e+308, so everithing will be ok
  for (size_t i = 0; i < n; i++)
    a[i] = i;
#pragma omp parallel
  {
#pragma parallel for
    for (size_t i = 1; i < n - 1; i++)
        b[i] = get_val (a[i - 1], a[i], a[i + 1]);
  }
  return 0;
}
