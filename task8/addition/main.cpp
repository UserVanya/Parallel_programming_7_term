#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
const bool DEBUG = 1;

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

bool
isSorted (const std::vector<int32_t> &toSort, int32_t startIndex,
          int32_t endIndex)
{
  for (size_t i = 1 + startIndex; i < endIndex + 1; i++)
    if (toSort[i] <= toSort[i - 1])
      return false;
  return true;
}

bool
isReverseSorted (const std::vector<int32_t> &toSort, int32_t startIndex,
                 int32_t endIndex)
{
  for (size_t i = endIndex + 1; i > 1 + startIndex; i--)
    {
      size_t j = i - 1;
      if (toSort[j - 1] < toSort[j])
        return false;
    }
  return true;
}

std::tuple<int32_t, int32_t> Separate(std::vector<int32_t> &toSort, int32_t startIndex, int32_t endIndex, int32_t pivot)
{
  size_t lo = startIndex, hi = endIndex + 1, j = startIndex;
  for (; j < hi; ) {
    if (toSort[j] < pivot) {
      std::swap(toSort[lo++], toSort[j++]);
    } else if (toSort[j] > pivot) {
      std::swap(toSort[j], toSort[--hi]);
    } else {
      ++j;
    } 
  }
  return std::tie(lo, hi);
}
void
qsort (std::vector<int32_t> &toSort, int32_t startIndex, int32_t endIndex)
{
  if (endIndex - startIndex < 1)
    return;
  if (isReverseSorted (toSort, startIndex, endIndex))
    {
      std::reverse (toSort.begin () + startIndex,
                    toSort.begin () + endIndex + 1);
      return;
    }
  if (isSorted (toSort, startIndex, endIndex))
    return;
  int32_t pivot = median (toSort[startIndex], toSort[endIndex],
                          toSort[(startIndex + endIndex) / 2]);
  auto [lo, hi] = Separate(toSort, startIndex, endIndex, pivot);
  

#pragma omp task shared(toSort)
  {
    if (lo > startIndex)
      {
        qsort (toSort, startIndex, lo);
      }
  }
#pragma omp task shared(toSort)
  {
    if (endIndex > hi)
      {
        qsort (toSort, hi, endIndex);
      }
  }
#pragma omp taskwait
}
void
qsort (std::vector<int32_t> &toSort)
{
  // std::cin.get();
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
  std::getline (std::cin, str);
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
          else
            {
              input >> v;
              isScanned = true;
            }
        }
      std::cout << v;
    }
  qsort (v);
  std::cout << v << std::endl;
}