#ifndef __TASK1__
#define __TASK1__

#include <cstddef>
#include <exception>
#include <initializer_list>
#include <stdexcept>

class DoubleArray {
private:
  double *_values;
  size_t _size;

public:
  DoubleArray();
  DoubleArray(const size_t size);
  DoubleArray(DoubleArray &value);
  ~DoubleArray();

  const size_t size() const;

  /* 1) */
  double &operator[](size_t index);
  double &operator[](size_t index) const;

  /* 2) */
  DoubleArray(std::initializer_list<double> l);
};

bool operator==(const DoubleArray &lhs, const DoubleArray &rhs);

/* 3) */
const DoubleArray &operator+(const DoubleArray &lhs, const DoubleArray &rhs);
const DoubleArray &operator-(const DoubleArray &lhs, const DoubleArray &rhs);
const DoubleArray &operator*(const DoubleArray &lhs, const DoubleArray &rhs);

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
  DoubleMatrix(std::initializer_list<DoubleArray> l);
};

bool operator==(const DoubleMatrix &lhs, const DoubleMatrix &rhs);

/* 3) */
const DoubleMatrix &operator+(const DoubleMatrix &lhs, const DoubleMatrix &rhs);
const DoubleMatrix &operator-(const DoubleMatrix &lhs, const DoubleMatrix &rhs);
const DoubleMatrix &operator*(const DoubleMatrix &lhs, const DoubleMatrix &rhs);

/* 4) */
const DoubleMatrix &operator*(const double &lhs, const DoubleMatrix &rhs);
const DoubleArray &operator*(const DoubleArray &lhs, const DoubleMatrix &rhs);
const DoubleArray &operator*(const DoubleMatrix &lhs, const DoubleArray &rhs);
const DoubleMatrix &matrix_bultiply(const DoubleMatrix &lhs,
                                    const DoubleMatrix &rhs);

#endif
