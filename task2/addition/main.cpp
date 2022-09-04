#include "omp.h"
#include <cassert>
#include <iostream>
int
main (int argc, char *argv[])
{
  assert (!argv[2]);
  assert (argv[1]);
  auto n = std::atoi (argv[1]);
  assert (n > 0);
  int sum = 0;
  #pragma omp parallel reduction(+: sum)
  {
    //The VAR sum in this context is private(local) 
    //The local VAR sum for each thread will be summed into global VAR sum after the parallel block
    #pragma omp for schedule(static)
    for (int i = 0; i <= n; i++)
      sum += i;
  }
  
  std::cout << "The sum of natural numbers from 1 to " << n
            << " inclusive is equal to " << sum << std::endl;
  return 0;
}