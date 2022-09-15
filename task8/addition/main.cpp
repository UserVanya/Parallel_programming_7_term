#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
template <typename T>
std::ostream &
operator<< (std::ostream &out, const std::vector<T> &v)
{
  bool isFirst = true;
  out << "[";
  for (const auto &el : v)
    {
      if (!isFirst)
        std::cout << ", ";
      isFirst = false;
      out << el;
    }
  out << "]";
  return out;
}
int32_t
median (int32_t a, int32_t b, int32_t c)
{
  int32_t max = std::max (std::max (a, b), c);
  int32_t min = std::min (std::min (a, b), c);
  return a + b + c - (min + max);
}
void
qsort (std::vector<int32_t> &toSort, int32_t startIndex, int32_t endIndex)
{
  std::cout << "qsort" << std::endl;
  int32_t pivot = median (toSort[startIndex], toSort[endIndex],
                          toSort[(startIndex + endIndex) / 2]);
  int32_t i = startIndex, j = endIndex;
  do
    {
      while (toSort[i] < pivot)
        {
          i++;
        }
      while (toSort[j] > pivot)
        {
          j--;
        }
      if (i <= j)
        {
          std::swap (toSort[i], toSort[j]);
          i++;
          j--;
        }
    }
  while (i <= j);
#pragma omp task shared(toSort)
  {
    if (j + 1 > startIndex)
      {
        qsort (toSort, startIndex, j + 1);
      }
  }
#pragma omp task shared(toSort)
  {
    if (endIndex > i)
      {
        qsort (toSort, i, endIndex);
      }
  }
#pragma omp taskwait
}
bool
isSorted (const std::vector<int32_t> &toSort)
{
  for (size_t i = 1; i < toSort.size (); i++)
    if (toSort[i] < toSort[i - 1])
      return false;
  return true;
}
bool
isReverseSorted (const std::vector<int32_t> &toSort)
{
  for (size_t i = toSort.size (); i > 1; i--)
    {
      size_t j = i - 1;
      if (toSort[j - 1] < toSort[j])
        return false;
    }
  return true;
}
void
qsort (std::vector<int32_t> &toSort)
{
  if (toSort.size () == 1)
    return;
  if (isReverseSorted (toSort))
    {
      std::reverse (toSort.begin (), toSort.end ());
      return;
    }
  if (isSorted (toSort))
    return;
  qsort (toSort, 0, toSort.size () - 1);
}
std::istream &
operator>> (std::istream &input, std::vector<int32_t> &v)
{
  if (input)
    {
      int32_t val;
      while (input >> val)
        v.push_back (val);
    }
  return input;
}
int
main ()
{
  std::vector<int32_t> v;
  bool isScanned = false;
  std::string str;
  std::getline(std::cin, str);    
  while (!isScanned)
    {
      bool contains_only_numeric
          = str.find_first_not_of ("1234567890 ") == std::string::npos;
      if (contains_only_numeric)
        {
          std::stringstream ss (str);
          ss >> v;
          isScanned = true;
        }
      else
        {
          std::ifstream input (str);
          if (!input.is_open ())
            std::cout << "Can't open file " << str << std::endl;
          else{
            input >> v;
            isScanned = true;
          } 
        }
        std::cout << v;
    }
  qsort (v);
  std::cout << v << std::endl;
}