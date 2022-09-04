#include "omp.h"
#include <cassert>
#include <vector>
#include <iostream>
#include <limits>

double get_val(double prev, double cur, double next)
{
  return prev * cur * next / 3;
}
int
main (int argc, char *argv[])
{
  size_t n = 100'000;
  n = 10;
  std::vector<double> a(n), b(n, 0);
  
  //std::cout << std::numeric_limits<double>::max() << std::endl; gives 1.79769e+308, 
  //so everithing will be ok
  for (size_t i = 0; i < n; i++)
    a[i] = static_cast<double>(i);
  #pragma omp parallel
  {
    #pragma parallel for firstprivate(a)
    for (size_t i = 1; i < n - 1; i++)
        b[i] = a[i - 1] * a[i] * a[i + 1] / 3;
  }
  return 0;
}
