#include <vector>
#include <cassert>
#include <cmath>
#include "linear-solver.h"
#include "auxiliary.h"
ReductionSolver::ReductionSolver(BandMatrix G, std::vector<double> g):
m_G(G),
m_g(g)
{
  assert(g.size() == G.Size());
  m_n = G.Size() + 1;
  bool isPowerOfTwo = !(m_n == 0) && !(m_n & (m_n - 1));
  assert(isPowerOfTwo);
  m_done.resize(m_n - 1);
  m_solution.resize(m_n - 1);
  m_lvlsNumber = round(log2(m_n));
  m_info.resize(m_lvlsNumber);
  for(size_t i = 0; i < G.Size(); i++)
    m_info.at(0).push_back(std::make_tuple(i == 0 ? 0 : G.At(i, i-1), G.At(i, i), i == G.Size() - 1 ? 0 : G.At(i, i + 1), g.at(i)));
}

eqInfo ReductionSolver::GetNewEquation(const eqInfo& eq1, const eqInfo& eq2, const eqInfo& eq3)
{
  auto [a1, b1, c1, f1] = eq1;
  auto [a2, b2, c2, f2] = eq2;
  auto [a3, b3, c3, f3] = eq3;
  auto alpha = -a2/b1;
  auto betta = -c2/b3;
  return std::make_tuple(alpha * a1, 
                         alpha * c1 + b2 + betta * a3,
                         betta * c3,
                         alpha * f1 + f2 + betta * f3);
}
double ReductionSolver::Solve(int i1, int i2, const eqInfo& eq)
{
  auto [a, b, c, f] = eq;
  auto result = f;
  if(i1 < 0)
    assert(a == 0);
  else
    result = result - a * m_solution.at(i1);
  if(i2 >= m_n - 1)
    assert(c == 0);
  else
    result = result - c * m_solution.at(i2);
  return result/b;
}
std::vector<double> ReductionSolver::SolveReduction()
{
  for (size_t lvl = 1; lvl < m_lvlsNumber; ++lvl)
  {
    for (size_t i = 0; i < m_n / pow(2, lvl) - 1; i++)
    {
      m_info.at(lvl).push_back(GetNewEquation(m_info.at(lvl-1).at(2 * i), 
                                              m_info.at(lvl-1).at(2 * i + 1), 
                                              m_info.at(lvl-1).at(2 * i + 2)));
    }
  }
  for (size_t tmp = m_lvlsNumber; tmp > 0; tmp--)
  {
    auto lvl = tmp - 1;
    for (size_t i = 0; i < m_n / pow(2, lvl) - 1; i++)
    {
      int step = m_n / pow(2, m_lvlsNumber - lvl);
      int middleIndex = step * (i + 1) - 1;
      if (!m_done.at(middleIndex))
      {
        m_solution.at(middleIndex) = Solve(middleIndex - step, middleIndex + step, m_info.at(lvl).at(i));   
        m_done.at(middleIndex) = true;
      }
    }
  }
  return m_solution;
}