#ifndef __TASK1__
#define __TASK1__

#include <cstddef>
#include <initializer_list>

class DoubleArray {
private:
  double *_values;
  size_t _size;

public:
  DoubleArray();
  DoubleArray(const size_t size);
  DoubleArray(DoubleArray &value);
  ~DoubleArray();

  size_t size();

  /* 1) */
  double &operator[](size_t index);

  /* 2) */
  DoubleArray(std::initializer_list<double> l);
};

class DoubleMatrix {
private:
  DoubleArray *_values;
  size_t _size;

public:
  DoubleMatrix();
  DoubleMatrix(const size_t row_count, const size_t col_count);
  DoubleMatrix(DoubleMatrix &value);
  ~DoubleMatrix();

  size_t size();

  /* 1) */
  DoubleArray &operator[](size_t index);
  DoubleArray get_row(size_t index);
  DoubleArray get_col(size_t index);
  DoubleArray get_main_diagonal();
  DoubleArray get_side_diagonal();

  /* 2) */
  DoubleMatrix(std::initializer_list<DoubleArray> l);
};

#endif
