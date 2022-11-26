#ifndef __BAND_MATRIX_H__
#define __BAND_MATRIX_H__
#include <vector>
#include <iostream>
class BandMatrix
{
public:
  BandMatrix(const std::vector<double>& l, const std::vector<double>& d, const std::vector<double>& u);
  double& At(size_t i, size_t j);
  const double& At(size_t i, size_t j) const;
  size_t Size() const;
private:
  std::vector<double> m_l, m_d, m_u;
};
std::ostream &operator<< (std::ostream &out, const BandMatrix &matrix);

#endif
