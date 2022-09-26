#ifndef __DOUBLEARRAY__
#define __DOUBLEARRAY__

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

  const DoubleArray operator+=(const DoubleArray &rhs);
  const DoubleArray operator-=(const DoubleArray &rhs);
  const DoubleArray operator*=(const DoubleArray &rhs);
};

bool operator==(const DoubleArray &lhs, const DoubleArray &rhs);

/* 3) */
const DoubleArray operator+(const DoubleArray &lhs, const DoubleArray &rhs);
const DoubleArray operator-(const DoubleArray &lhs, const DoubleArray &rhs);
const DoubleArray operator*(const DoubleArray &lhs, const DoubleArray &rhs);

/* 5) */
const DoubleArray operator+(const DoubleArray &lhs, const double &rhs);
const DoubleArray operator-(const DoubleArray &lhs, const double &rhs);

#endif
