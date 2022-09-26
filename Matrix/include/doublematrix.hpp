#ifndef __DOUBLEMATRIX__
#define __DOUBLEMATRIX__

#include <cstddef>
#include <exception>
#include <initializer_list>
#include <stdexcept>

#include <doublearray.hpp>

class DoubleMatrix {
private:
  DoubleArray *_values;
  size_t _size;

public:
  DoubleMatrix();
  DoubleMatrix(const size_t row_count, const size_t col_count);
  DoubleMatrix(DoubleMatrix &value);
  ~DoubleMatrix();

  const size_t size() const;

  /* 1) */
  DoubleArray &operator[](size_t index);
  DoubleArray &operator[](size_t index) const;
  DoubleArray get_row(size_t index);
  DoubleArray get_col(size_t index);
  DoubleArray get_main_diagonal();
  DoubleArray get_side_diagonal();

  /* 2) */
  DoubleMatrix(std::initializer_list<std::initializer_list<double>> l);

  const DoubleMatrix operator+=(const DoubleMatrix &rhs);
  const DoubleMatrix operator-=(const DoubleMatrix &rhs);
  const DoubleMatrix operator*=(const DoubleMatrix &rhs);

  /* 6) */
  const DoubleMatrix transpose();
  const DoubleMatrix inverse();

  /* 6) */
  const double get_determinant();
};

bool operator==(const DoubleMatrix &lhs, const DoubleMatrix &rhs);

/* 3) */
const DoubleMatrix operator+(const DoubleMatrix &lhs, const DoubleMatrix &rhs);
const DoubleMatrix operator-(const DoubleMatrix &lhs, const DoubleMatrix &rhs);
const DoubleMatrix operator*(const DoubleMatrix &lhs, const DoubleMatrix &rhs);

/* 4) */
const DoubleMatrix operator*(const double &lhs, const DoubleMatrix &rhs);
const DoubleArray operator*(const DoubleArray &lhs, const DoubleMatrix &rhs);
const DoubleArray operator*(const DoubleMatrix &lhs, const DoubleArray &rhs);
const DoubleMatrix matrix_multiply(const DoubleMatrix &lhs,
                                   const DoubleMatrix &rhs);

/* 5) */
const DoubleMatrix operator+(const DoubleMatrix &lhs, const double &rhs);
const DoubleMatrix operator-(const DoubleMatrix &lhs, const double &rhs);

const DoubleMatrix add_arr_to_matrix(DoubleMatrix &lhs, DoubleArray &rhs,
                                     size_t ind, bool is_row);
const DoubleMatrix substract_arr_from_matrix(DoubleMatrix &lhs,
                                             DoubleArray &rhs, size_t ind,
                                             bool is_row);

#endif
