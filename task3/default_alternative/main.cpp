#include "omp.h"
#include <cassert>
#include <vector>
#include <iostream>
#include <limits>
template <typename T>
std::ostream &operator<< (std::ostream &out, const std::vector<T> &v);

template <typename T>
std::ostream &
operator<< (std::ostream &out, const std::vector<T> &v)
{
  bool isFirst = true;
  out << "[";
  for (const auto &el : v)
    {
      if (!isFirst)
        std::cout << ", ";
      isFirst = false;
      out << el;
    }
  out << "]";
  return out;
}
int
main (int argc, char *argv[])
{
  size_t n = 100'000;
  n = 10;
  std::vector<size_t> a(n), b(n, 0);
  
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
// an ability to test
//  std::cout << b << std::endl;
  return 0;
}
