#include <iostream>
#include <fstream>
#include <cassert>
#include "linear-solver.h"
#include "band-matrix.h"
#include "non-linear-solver.h"
#include "auxiliary.h"
int main(int argc, char *argv[])
{
  assert (!argv[2]);
  assert (argv[1]);
  double b = atof(argv[1]);
  NonLinearSolver s(0.0, 1.0, 1.0, b, [](long double x, long double y){ return exp(-y);}, [](long double x, long double y){ return -exp(-y);}, 11);
  std::stringstream ss;
  ss << "b=" << b << ".txt";
  std::ofstream out(ss.str());
  
  auto res = s.Solve(1e-10);
  out << "x" << "\t" << "y" << std::endl;
  for (size_t i = 0; i < res.first.size(); i++)
  {
    out << res.first.at(i) << "\t" << res.second.at(i) << std::endl;
  }
}