#include <iostream>
#include "linear-solver.h"
#include "band-matrix.h"
#include "non-linear-solver.h"
#include "auxiliary.h"
int main()
{
  NonLinearSolver s(0.0, 1.0, 1.0, 1.0, [](long double x, long double y){ return exp(-y);}, [](long double x, long double y){ return -exp(-y);}, 3);
  std::cout << s.Solve(1e-20).second;
}