#include "isolated_area.h"

IsolatedArea::IsolatedArea (size_t m, size_t n)
    : m_temperature (m * n, 0), m_m (m), m_n (n)
{
  for (size_t i = 0; i < m_m; i++)
    {
      m_temperature.at (i * m_n) = 100;
      if (i != 0)
        m_temperature.at (i * m_n - 1) = 100;
    }
  for (size_t j = 0; j < m_n; j++)
    {
      m_temperature.at ((m_m - 1) * m_n + j) = 100;
    }

  m_out.open ("out.txt", std::ios::out);
  assert (m_out.is_open ());
}

void
IsolatedArea::Process (std::vector<double> &tmp)
{
#pragma omp parallel for
  for (size_t j = 0; j < m_n; j++)
    for (size_t i = 0; i < m_m; i++)
      tmp.at (i * m_n + j) = GetCloseCellsAverage (i, j);
}

double
IsolatedArea::GetCloseCellsAverage (size_t i, size_t j)
{
  assert(i < m_m);
  assert(j < m_n);
  double up = i > 0 ? m_temperature.at ((i - 1) * m_n + j) : 0;
  double down = i < m_m - 1 ? m_temperature.at ((i + 1) * m_n + j) : 0;
  double left = j > 0 ? m_temperature.at (i * m_n + j - 1) : 0;

  double right = j < m_n - 1 ? m_temperature.at (i * m_n + j + 1) : 0;
  return (up + down + left + right) / 4;
}

bool
IsolatedArea::IsAccuracyAchieved (const std::vector<double> &toCompare,
                                  double epsilon)
{
  bool isAchieved = true;
#pragma omp parallel for
  for (size_t j = 0; j < m_n; j++)
    for (size_t i = 0; i < m_m; i++)
      if (std::abs (toCompare.at (i * m_n + j)
                    - m_temperature.at (i * m_n + j))
          > epsilon)
        isAchieved = false;
  return isAchieved;
}

void
IsolatedArea::StartSimulation (double epsilon)
{
  std::vector<double> tmp (m_m * m_n, 0);
  bool isFirst = true;
  while (!IsAccuracyAchieved (tmp, epsilon))
    {
      if (!isFirst)
        m_temperature = tmp;
      isFirst = false;
      PrintArea ();
      Process (tmp);
      m_out << std::endl;
    }
}

void
IsolatedArea::PrintArea ()
{
  for (size_t i = 0; i < m_m; i++)
    {
      bool isFirstRow = true;
      for (size_t j = 0; j < m_n; j++)
        {
          m_out << std::setw (16) << std::setprecision (6) << std::fixed
                << m_temperature.at (i * m_n + j);
          if (!isFirstRow)
            m_out << " ";
          isFirstRow = false;
        }
      m_out << std::endl;
    }
}