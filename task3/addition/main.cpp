#include "omp.h"
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

int
main (int argc, char *argv[])
{
  size_t n = 100'000;
  std::vector<double> a (n);
  // std::cout << std::numeric_limits<double>::max() << std::endl;
  // gives 1.79769e+308, so everithing will be ok
  for (size_t i = 0; i < n; i++) 
    a[i] = static_cast<double> (i);
#pragma omp parallel
  {
    auto threadIndex = omp_get_thread_num();
    auto totalThreads = omp_get_max_threads();
    //setting range for each thread
    size_t startIndex = threadIndex == 0 ? 1 : 1.0 * threadIndex / totalThreads * n,
           endIndex   = threadIndex == totalThreads - 1 ? n - 1 : 1.0 * (threadIndex + 1) / totalThreads * n;
    //buffer required because we will change vector a value
    std::vector<double> buffer (3, 0);
    double lastVal = 0;
    buffer[0] = a[startIndex - 1];
    buffer[1] = a[startIndex];
    buffer[2] = a[startIndex + 1];
    //lastVal required because each thread will change a[endIndex] of prev thread.
    lastVal = a[endIndex]; 
#pragma omp barrier
    for (size_t i = startIndex; i < endIndex; i++)
      {
        a[i] = buffer[0] * buffer[1] * buffer[2] / 3;
        buffer.erase(buffer.begin());
        if(i == endIndex - 2)
          buffer.push_back(lastVal);
        else
          buffer.push_back(a[i + 2]);
      }
  }
  a[n - 1] = 0;
  return 0;
}
