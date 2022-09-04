#pragma once
#include <iostream>
#include <vector>
class Matrix
{
public:
  /**
   * @brief Construct a new Matrix with rowsNum number of rows and colsNum number of columns.
   * 
   * @param rowsNum 
   * @param colsNum 
   * @param isRandom If true each matrix element value will be chosen from 
   * uniform real distribution with min = -2.0 and max = 2.0
   */
  Matrix(size_t rowsNum, size_t colsNum, bool isRandom = true);
  ~Matrix();
  /**
   * @brief Get the number of matrix columns
   * 
   * @return size_t 
   */
  inline size_t GetColsNum() const;
  /**
   * @brief Get the number of matrix rows
   * 
   * @return size_t 
   */
  inline size_t GetRowsNum() const;
  /**
   * @brief Returns value from position Matrix[rowIndex + 1][colIndex + 1] 
   * 
   * @param rowIndex 
   * @param colIndex 
   * @return double 
   */
  inline double At(size_t rowIndex, size_t colIndex) const;
  /** Returns a reference to the element from position Matrix[rowIndex + 1][colIndex + 1] 
   * @brief 
   * 
   * @param rowIndex 
   * @param colIndex 
   * @return double& 
   */
  inline double& At(size_t rowIndex, size_t colIndex);
private:
  double* m_data;
  size_t m_numRows, m_numCols;
};
Matrix operator*(const Matrix& lhs, const Matrix& rhs);
std::ostream& operator<< (std::ostream& out, const Matrix& matrix);