#include "matrix.h"
#include "omp.h"
#include <cassert>
#include <iomanip>
#include <random>
Matrix::Matrix (size_t rowsNum, size_t colsNum, bool isRandom)
{
  m_data = new double[rowsNum * colsNum];
  m_numRows = rowsNum;
  m_numCols = colsNum;
  if (isRandom)
    {
      std::random_device
          rd; // Will be used to obtain a seed for the random number engine
      std::mt19937 gen (
          rd ()); // Standard mersenne_twister_engine seeded with rd()
      std::uniform_real_distribution<double> distribution (-2.0, 2.0);
#pragma parallel for
      for (int i = 0; i < rowsNum * colsNum; i++)
        m_data[i] = distribution (gen);
    }
}

size_t
Matrix::GetRowsNum () const
{
  return m_numRows;
}
size_t
Matrix::GetColsNum () const
{
  return m_numCols;
}
double
Matrix::At (size_t rowIndex, size_t colIndex) const
{
  return m_data[rowIndex * m_numCols + colIndex];
}
double &
Matrix::At (size_t rowIndex, size_t colIndex)
{
  return m_data[rowIndex * m_numCols + colIndex];
}

Matrix
operator* (const Matrix &lhs, const Matrix &rhs)
{
  Matrix result (lhs.GetRowsNum (), rhs.GetColsNum (), false);
  auto size = lhs.GetColsNum ();
#pragma omp parallel for schedule(guided) if (size >= 100)
  for (size_t i = 0; i < lhs.GetRowsNum (); i++)
    for (size_t k = 0; k < size; k++)
      {
        auto tmp = lhs.At (i, k);
        for (size_t j = 0; j < k; j++)
          result.At (i, j) += tmp * rhs.At (k, j);
      }
  return result;
}
std::ostream &
operator<< (std::ostream &out, const Matrix &matrix)
{
  for (size_t i = 0; i < matrix.GetRowsNum (); i++)
    {
      for (size_t j = 0; j < matrix.GetColsNum (); j++)
        {
          out << std::setw (5) << std::fixed << std::setprecision (2)
              << matrix.At (i, j);
        }
      out << std::endl;
    }
  return out;
}
Matrix::~Matrix()
{
  delete [] m_data;
  m_data = nullptr;
}