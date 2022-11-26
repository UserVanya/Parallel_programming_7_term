#include "non-linear-solver.h"
#include "band-matrix.h"
#include "linear-solver.h"
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
double
NonLinearSolver::g (size_t dotIndex, double y_l, double y, double y_u)
{
  assert (dotIndex >= 1 && dotIndex <= m_dots.size () - 2);
  assert (!(dotIndex == 1) || y_l == m_a);
  assert (!(dotIndex == m_dots.size () - 2) || y_u == m_b);
  return y_u - 2 * y + y_l
         - m_h * m_h
               * ((5.0 / 6 * m_f (m_dots.at (dotIndex), y))
                  + 1.0 / 12
                        * (m_f (m_dots.at (dotIndex - 1), y_l)
                           + m_f (m_dots.at (dotIndex + 1), y_u)));
}
double
NonLinearSolver::l (size_t dotIndex, double y_l)
{
  assert (dotIndex >= 2 && dotIndex <= m_dots.size () - 2);
  // std::cout << m_h * m_h * 1 / 12 * m_fy (m_dots.at (dotIndex - 1), y_l) <<
  // std::endl; std::cout << std::setprecision(12)<< 1 - m_h * m_h * 1 / 12 *
  // m_fy (m_dots.at (dotIndex - 1), y_l) << std::endl;
  return 1 - m_h * m_h * 1 / 12 * m_fy (m_dots.at (dotIndex - 1), y_l);
}
double
NonLinearSolver::u (size_t dotIndex, double y_u)
{
  assert (dotIndex >= 1 && dotIndex <= m_dots.size () - 3);
  return 1 - m_h * m_h * 1 / 12 * m_fy (m_dots.at (dotIndex + 1), y_u);
}
double
NonLinearSolver::d (size_t dotIndex, double y)
{
  assert (dotIndex >= 1 && dotIndex <= m_dots.size () - 2);
  return -2 - m_h * m_h * 5 / 6 * m_fy (m_dots.at (dotIndex), y);
}

NonLinearSolver::NonLinearSolver (double x0, double x1, double a, double b,
                                  std::function<double (double, double)> f,
                                  std::function<double (double, double)> fy,
                                  size_t stepsPower)
    : m_f (f), m_fy (fy), m_x0 (x0), m_x1 (x1), m_a (a), m_b (b),
      m_stepsNumber (pow (2, stepsPower))
{
  m_h = (x1 - x0) / m_stepsNumber;
  for (size_t i = 0; i * m_h <= m_x1; i++)
    m_dots.push_back (x0 + i * m_h);
  m_solution.resize (m_dots.size ());
  m_solution.front () = m_a;
  m_solution.back () = m_b;
}
double
NonLinearSolver::Rho (const std::vector<double> &a,
                      const std::vector<double> &b)
{
  assert (a.size () == b.size ());
  double sum = 0;
  for (size_t i = 0; i < a.size (); i++)
    sum += (a[i] - b[i]) * (a[i] - b[i]);
  return sqrt (sum);
}

std::vector<double>
NonLinearSolver::GetFullg (const std::vector<double> &sol)
{
  std::vector<double> gVector (m_dots.size () - 2);
  for (int i = 1; i < m_dots.size () - 1; i++)
    gVector[i - 1] = g (i, i == 1 ? m_a : sol.at (i - 2), sol.at (i - 1),
                        i == m_dots.size () - 2 ? m_b : sol.at (i));
  return gVector;
}
std::vector<double>
NonLinearSolver::GetFullL (const std::vector<double> &sol)
{
  std::vector<double> lVector (m_dots.size () - 3);
  for (int i = 2; i < m_dots.size () - 1; i++)
    lVector[i - 2] = l (i, sol.at (i - 2));
  return lVector;
}
std::vector<double>
NonLinearSolver::GetFullU (const std::vector<double> &sol)
{
  std::vector<double> uVector (m_dots.size () - 3);
  for (int i = 1; i < m_dots.size () - 2; i++)
    uVector[i - 1] = u (i, sol.at (i));
  return uVector;
}
std::vector<double>
NonLinearSolver::GetFullD (const std::vector<double> &sol)
{
  std::vector<double> dVector (m_dots.size () - 2);
  for (int i = 1; i < m_dots.size () - 1; i++)
    dVector[i - 1] = d (i, sol.at (i - 1));
  return dVector;
}
std::pair<std::vector<double>, std::vector<double> >
NonLinearSolver::Solve (double eps)
{
  std::vector<double> internalSolutionPrev (m_dots.size () - 2, 1.0);
  std::vector<double> internalSolutionCurrent = internalSolutionPrev;
  // std::cout << "curr: " << internalSolutionCurrent << std::endl;
  do
    {
      BandMatrix G (GetFullL (internalSolutionCurrent),
                    GetFullD (internalSolutionCurrent),
                    GetFullU (internalSolutionCurrent));
      // std::cout << GetFullL(internalSolutionCurrent) << std::endl;;
      ReductionSolver redSolv (G, GetFullg (internalSolutionCurrent));
      auto p = redSolv.SolveReduction ();
      internalSolutionPrev = internalSolutionCurrent;
      internalSolutionCurrent = internalSolutionCurrent - p;
    }
  while (Rho (internalSolutionPrev, internalSolutionCurrent) > eps);
  internalSolutionCurrent.insert (internalSolutionCurrent.begin (), m_a);
  internalSolutionCurrent.push_back (m_b);
  m_solution = internalSolutionCurrent;
  return std::make_pair (m_dots, m_solution);
}
std::vector<double>
operator- (const std::vector<double> &lhs, const std::vector<double> &rhs)
{
  assert (lhs.size () == rhs.size ());
  std::vector<double> result (rhs.size ());
  for (size_t i = 0; i < rhs.size (); i++)
    result.at (i) = lhs.at (i) - rhs.at (i);
  return result;
}
