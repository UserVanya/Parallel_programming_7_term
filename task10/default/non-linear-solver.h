#ifndef __NON_LINEAR_SOLVER_H__
#define _NON_LINEAR_SOLVER_H__
#include <functional>
#include <vector>
#include <iostream>
class NonLinearSolver
{
public:
  NonLinearSolver(double x0, double x1, double a, double b, std::function<double(double, double)> f, std::function<double(double, double)> fy, size_t stepsPower);
  std::vector<double> Solve(double eps);
  double g(size_t dotIndex, double y_l, double y, double y_u);
  double l(size_t dotIndex, double y_l);
  double u(size_t dotIndex, double y_u);
  double d(size_t dotIndex, double y);
  std::vector<double> GetFullg(const std::vector<double>& sol);
  std::vector<double> GetFullL(const std::vector<double>& sol);
  std::vector<double> GetFullU(const std::vector<double>& sol);
  std::vector<double> GetFullD(const std::vector<double>& sol);
  double Rho(const std::vector<double>& a, const std::vector<double>& b);
private:
   std::function<double(double/*x*/, double/*y*/)> m_f, m_fy;
   double m_x0, m_x1, m_a, m_b;
   size_t m_stepsNumber;
   double m_h;
   std::vector<double> m_dots, m_solution;
};
std::vector<double> operator-(const std::vector<double>& lhs, const std::vector<double>& rhs);

std::ostream & operator<< (std::ostream &out, const std::vector<double> &v);
#endif