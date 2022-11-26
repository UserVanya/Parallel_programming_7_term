#ifndef __SOLVER_H__
#define __SOLVER_H__
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>
#include "band-matrix.h"
using eqInfo = std::tuple<double, double, double, double>;
using lvlInfo = std::vector<eqInfo>; 

class ReductionSolver
{
public:
  ReductionSolver(BandMatrix G, std::vector<double> g);
  void ForwardReduction();
  void BackwardReduction();
  double Solve(int i1, int i2, const eqInfo& eq);
  eqInfo GetNewEquation(const eqInfo& eq1, const eqInfo& eq2, const eqInfo& eq3);
  std::vector<double> SolveReduction();
private:
  std::vector<lvlInfo> m_info;
  size_t m_lvlsNumber;
  size_t m_n; 
  BandMatrix m_G;
  std::vector<bool> m_done;
  std::vector<double> m_solution;
  std::vector<double> m_g;
};
#endif
