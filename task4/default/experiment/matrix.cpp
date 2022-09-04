#include "matrix.h"
#include "omp.h"
#include <cassert>
#include <random>
#include <iomanip>
Matrix::Matrix(size_t rowsNum, size_t colsNum, bool isRandom)
{
  m_data = std::vector<double>(rowsNum * colsNum, 0);
  m_numRows = rowsNum;
  m_numCols = colsNum;
  if(isRandom){
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> distribution(-2.0, 2.0);
    for (int i = 0; i < rowsNum * colsNum; i++)
      m_data.at(i) = distribution(gen);
  }
}
size_t Matrix::GetRowsNum() const{
  return m_numRows;
}
size_t Matrix::GetColsNum() const{
  return m_numCols;
}
double Matrix::At(size_t rowIndex, size_t colIndex) const
{
  return m_data.at(rowIndex * m_numCols + colIndex);
}
double& Matrix::At(size_t rowIndex, size_t colIndex)
{
  return m_data.at(rowIndex * m_numCols + colIndex);
}
double
MultiplyVectors (const Matrix &lhs, size_t rowIndex, const Matrix &rhs,
                 size_t colIndex)
{
  assert (lhs.GetColsNum () == rhs.GetRowsNum ());
  double result = 0;
//#pragma parallel for reduction(+ : result)
  for (size_t i = 0; i < lhs.GetColsNum (); i++)
      result += lhs.At (rowIndex, i) * rhs.At (i, colIndex);
  return result;
}
Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
  Matrix result (lhs.GetRowsNum (), rhs.GetColsNum (), false);
#pragma omp parallel for schedule(dynamic, 2) if(lhs.GetColsNum() >= 50)
  for (size_t i = 0; i < lhs.GetRowsNum (); i++)
      for (size_t j = 0; j < rhs.GetColsNum (); j++)
          result.At(i, j) = MultiplyVectors(lhs, i, rhs, j);
  return result;
}
std::ostream& operator<< (std::ostream& out, const Matrix& matrix){
  for (size_t i = 0; i < matrix.GetRowsNum(); i++){
    for (size_t j = 0; j < matrix.GetColsNum(); j++){
      out << std::setw(5) << std::fixed << std::setprecision(2) << matrix.At(i, j);
    }
    out << std::endl;
  }
  return out;
}
