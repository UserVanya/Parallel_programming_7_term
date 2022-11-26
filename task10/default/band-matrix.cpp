#include "band-matrix.h"
#include <cassert>
#include <iostream>
#include <cmath>
#include <iomanip>
BandMatrix::BandMatrix (const std::vector<double> &l,
                        const std::vector<double> &d,
                        const std::vector<double> &u)
{
  assert (d.size () > 0);
  assert (l.size () == d.size () - 1);
  assert (u.size () == d.size () - 1);
  m_l = l;
  m_d = d;
  m_u = u;
}
double &
BandMatrix::At (size_t i, size_t j)
{
  assert (i >= 0 && i < m_d.size ());
  assert (j >= 0 && j < m_d.size ());
  assert (abs((int)i - (int)j) <= 1);
  if(i > j) return m_l.at(i - 1);
  else if (i == j) return m_d.at(i);
  else return m_u.at(i);
}
const double &
BandMatrix::At (size_t i, size_t j) const
{
  assert (i >= 0 && i < m_d.size ());
  assert (j >= 0 && j < m_d.size ());
  assert (abs((int)i - (int)j) <= 1);
  if(i > j) return m_l.at(i - 1);
  else if (i == j) return m_d.at(i);
  else return m_u.at(i);
}
size_t BandMatrix::Size() const
{
  return m_d.size();
}

std::ostream &
operator<< (std::ostream &out, const BandMatrix &matrix)
{
  for (size_t i = 0; i < matrix.Size (); i++)
    {
      for (size_t j = 0; j < matrix.Size (); j++)
        {
          out << std::setw (20) << std::fixed << std::setprecision (15);
            
          if(abs((int)i - (int)j) <= 1)
            out << matrix.At (i, j);
          else 
            out << 0;
        }
      out << std::endl;
    }
  return out;
}