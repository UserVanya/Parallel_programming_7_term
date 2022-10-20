

#include "isolated_area.h"

int
main (int argc, char *argv[])
{
  assert (argv[1]);
  assert (argv[2]);
  assert (!argv[3]);
  size_t m = atoi (argv[1]), n = atoi (argv[2]);
  IsolatedArea area (m, n);
  area.StartSimulation (0.001);
  //area.~IsolatedArea ();
}
