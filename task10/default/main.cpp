#include <iostream>
#include "linear-solver.h"
#include "band-matrix.h"
#include "non-linear-solver.h"

int main()
{
  NonLinearSolver s(0.0, 1.0, 1.0, 1.0, [](double x, double y){ return exp(y);}, [](double x, double y){ return exp(y);}, 5);
  std::cout << s.Solve(1e-1);
}