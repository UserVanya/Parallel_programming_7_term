#include "omp.h"
#include <cassert>
#include <iostream>
int
main (int argc, char *argv[])
{
  int sum = 0, n;
  std::cout << "Enter N:" << std::endl;
  std::cin >> n;
  assert(n > 0);
#pragma omp parallel for
  for (int i = 0; i <= n; i++)
    {
// Ensure no simultaneous rading&writing to VAR sum
#pragma omp atomic
      sum += i;
    }
  // This variation of sum will work much more longer than the same without omp
  // atomic because of omp atomic blocking, but will give correct result
  std::cout << "The sum of natural numbers from 1 to " << n
            << " inclusive is equal to " << sum << std::endl;
  return 0;
}
