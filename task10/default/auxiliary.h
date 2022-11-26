#ifndef __AUXILIARY_H__
#define __AUXILIARY_H__
#include <iomanip>
#include <iostream>
#include <vector>

std::ostream &operator<< (std::ostream &out, const std::vector<double> &v);
#endif