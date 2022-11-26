#include "auxiliary.h"
std::ostream &operator<< (std::ostream &out, const std::vector<double> &v)
{
  bool isFirst = true;
  out << "[";
  for (const auto &el : v)
    {
      if (!isFirst)
        std::cout << ", ";
      isFirst = false;
      out << std::setprecision(20) << el;
    }
  out << "]";
  return out;
}
