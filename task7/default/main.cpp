

#include "isolated_area.h"

int
main (int argc, char *argv[])
{
  assert (argv[1]);
  assert (argv[2]);
  assert (!argv[3]);
  size_t m = atoi (argv[1]), n = atoi (argv[2]);
  IsolatedArea area (m, n);
  struct timespec begin, end;
  std::cout << "Started..." << std::endl;
  clock_gettime (CLOCK_REALTIME, &begin);
  area.StartSimulation (0.001);
  clock_gettime (CLOCK_REALTIME, &end);
  std::cout << "Done!" << std::endl;
  double elapsed = end.tv_sec - begin.tv_sec;
  elapsed += (end.tv_nsec - begin.tv_nsec) / 1'000'000'000.0; 
  std::cout << "Elapsed time: " << elapsed << std::endl;
  //area.~IsolatedArea ();
}
