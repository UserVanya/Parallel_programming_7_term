#include "omp.h"
#include <iostream>

int main(){
  #pragma omp parallel
  {
    auto myId = omp_get_thread_num();
    std::cout << myId << std::endl;
  }
  return 0;
}
