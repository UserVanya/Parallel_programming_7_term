#pragma ones
#include "omp.h"
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
class IsolatedArea
{
public:
  IsolatedArea (size_t m, size_t n);
  void StartSimulation (double epsilon);
  
private:
  void Process (std::vector<double> &tmp);
  double GetCloseCellsAverage (size_t i, size_t j);
  bool IsAccuracyAchieved (const std::vector<double> &toCompare,
                           double epsilon);
  void PrintArea ();
  std::vector<double> m_temperature;
  size_t m_m, m_n;
  std::ofstream m_out;
};