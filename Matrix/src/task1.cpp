#include <iostream>
#include <task1.hpp>

DoubleArray::DoubleArray() : _values(nullptr), _size(0) {}

DoubleArray::DoubleArray(const size_t size) : _values(nullptr), _size(size) {
  _values = new double[size];
  for (size_t i = 0; i < _size; ++i) {
    _values[i] = 0;
  }
}

DoubleArray::DoubleArray(DoubleArray &value)
    : _values(nullptr), _size(value._size) {
  _values = new double[_size];
  for (size_t i = 0; i < _size; ++i) {
    _values[i] = value._values[i];
  }
}

DoubleArray::~DoubleArray() { delete[] _values; }

const size_t DoubleArray::size() const { return _size; }

double &DoubleArray::operator[](size_t index) {
  if (index < _size) {
    return _values[index];
  }
  throw std::runtime_error("Index out of bounds");
}

double &DoubleArray::operator[](size_t index) const {
  if (index < _size) {
    return _values[index];
  }
  throw std::runtime_error("Index out of bounds");
}

DoubleArray::DoubleArray(std::initializer_list<double> l) {
  _size = l.size();
  size_t i = 0;
  _values = new double[_size];
  for (double e : l) {
    _values[i++] = e;
  }
}

bool operator==(const DoubleArray &lhs, const DoubleArray &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  for (size_t i = 0; i < lhs.size(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

const DoubleArray &operator+(const DoubleArray &lhs, const DoubleArray &rhs) {
  if (lhs.size() != rhs.size()) {
    throw std::runtime_error("Dimensions have to be the same");
  }
  DoubleArray res = DoubleArray(lhs.size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    res[i] = lhs[i] + rhs[i];
  }
  return *(new DoubleArray(res));
}

const DoubleArray &operator-(const DoubleArray &lhs, const DoubleArray &rhs) {
  if (lhs.size() != rhs.size()) {
    throw std::runtime_error("Dimensions have to be the same");
  }
  DoubleArray *res = new DoubleArray(lhs.size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    res[i] = lhs[i] - rhs[i];
  }
  return *res;
}

const DoubleArray &operator*(const DoubleArray &lhs, const DoubleArray &rhs) {
  if (lhs.size() != rhs.size()) {
    throw std::runtime_error("Dimensions have to be the same");
  }
  DoubleArray *res = new DoubleArray(lhs.size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    res[i] = lhs[i] * rhs[i];
  }
  return *res;
}

DoubleMatrix::DoubleMatrix() : _values(nullptr), _size(0) {}

DoubleMatrix::DoubleMatrix(const size_t row_count, const size_t col_count)
    : _values(nullptr), _size(row_count) {
  _values = new DoubleArray[_size];
  for (size_t i = 0; i < row_count; ++i) {
    _values[i] = *(new DoubleArray(row_count));
    for (size_t j = 0; j < col_count; ++j) {
      _values[i][j] = 0;
    }
  }
}

DoubleMatrix::DoubleMatrix(DoubleMatrix &value)
    : _values(nullptr), _size(value._size) {
  _values = new DoubleArray[value._size];
  for (size_t i = 0; i < value._size; ++i) {
    _values[i] = *(new DoubleArray(value[i].size()));
    for (size_t j = 0; j < value[i].size(); ++j) {
      _values[i][j] = value._values[i][j];
    }
  }
}
DoubleMatrix::~DoubleMatrix() { delete[] _values; }

const size_t DoubleMatrix::size() const { return _size; }

DoubleArray &DoubleMatrix::operator[](size_t index) {
  if (index < _size) {
    return _values[index];
  }
  throw std::runtime_error("Index out of bounds");
}

DoubleArray &DoubleMatrix::operator[](size_t index) const {
  if (index < _size) {
    return _values[index];
  }
  throw std::runtime_error("Index out of bounds");
}

DoubleArray DoubleMatrix::get_row(size_t index) {
  DoubleArray res(_values[index]);
  return res;
}

DoubleArray DoubleMatrix::get_col(size_t index) {
  DoubleArray res(_size);
  for (size_t i = 0; i < _size; ++i) {
    res[i] = _values[index][i];
  }
  return res;
}

DoubleArray DoubleMatrix::get_main_diagonal() {
  DoubleArray res(_size);
  for (size_t i = 0; i < _size; ++i) {
    res[i] = _values[i][i];
  }
  return res;
}

DoubleArray DoubleMatrix::get_side_diagonal() {
  DoubleArray res(_size);
  for (size_t i = 0; i < _size; ++i) {
    res[i] = _values[i][_size - 1 - i];
  }
  return res;
}

DoubleMatrix::DoubleMatrix(std::initializer_list<DoubleArray> l) {
  _size = l.size();
  size_t i = 0;
  for (auto &e : l) {
    _values[i++] = e;
  }
}

bool operator==(const DoubleMatrix &lhs, const DoubleMatrix &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  for (size_t i = 0; i < lhs.size(); ++i) {
    if (!(lhs[i] == rhs[i])) {
      return false;
    }
  }
  return true;
}

const DoubleMatrix &operator+(const DoubleMatrix &lhs,
                              const DoubleMatrix &rhs) {
  if ((lhs.size() != rhs.size()) || (lhs[0].size() != rhs[0].size())) {
    throw std::runtime_error("Dimensions have to be the same");
  }
  DoubleMatrix *res = new DoubleMatrix(lhs.size(), lhs[0].size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    for (size_t j = 0; j < lhs[0].size(); ++j) {
      res[i][j] = lhs[i][j] + rhs[i][j];
    }
  }
  return *res;
}

const DoubleMatrix &operator-(const DoubleMatrix &lhs,
                              const DoubleMatrix &rhs) {

  if ((lhs.size() != rhs.size()) || (lhs[0].size() != rhs[0].size())) {
    throw std::runtime_error("Dimensions have to be the same");
  }
  DoubleMatrix *res = new DoubleMatrix(lhs.size(), lhs[0].size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    for (size_t j = 0; j < lhs[0].size(); ++j) {
      res[i][j] = lhs[i][j] - rhs[i][j];
    }
  }
  return *res;
}

const DoubleMatrix &operator*(const DoubleMatrix &lhs,
                              const DoubleMatrix &rhs) {

  if ((lhs.size() != rhs.size()) || (lhs[0].size() != rhs[0].size())) {
    throw std::runtime_error("Dimensions have to be the same");
  }
  DoubleMatrix *res = new DoubleMatrix(lhs.size(), lhs[0].size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    for (size_t j = 0; j < lhs[0].size(); ++j) {
      res[i][j] = lhs[i][j] * rhs[i][j];
    }
  }
  return *res;
}

const DoubleMatrix &operator*(const double &lhs, const DoubleMatrix &rhs) {
  DoubleMatrix *res = new DoubleMatrix(rhs.size(), rhs[0].size());
  for (size_t i = 0; i < rhs.size(); ++i) {
    for (size_t j = 0; j < rhs[0].size(); ++j) {
      res[i][j] = rhs[i][j] * lhs;
    }
  }
  return *res;
}
const DoubleArray &operator*(const DoubleArray &lhs, const DoubleMatrix &rhs) {
  if ((lhs.size() != rhs[0].size())) {
    throw std::runtime_error("Dimensions have to be (m), (n,m)");
  }
  DoubleArray *res = new DoubleArray(lhs.size());
  for (size_t j = 0; j < rhs[0].size(); ++j) {
    for (size_t i = 0; i < rhs.size(); ++i) {
      res[j] = res[j] + lhs[j] * rhs[i][j];
    }
  }
  return *res;
}
const DoubleArray &operator*(const DoubleMatrix &lhs, const DoubleArray &rhs) {
  if ((rhs.size() != lhs[0].size())) {
    throw std::runtime_error("Dimensions have to be (m), (n,m)");
  }
  DoubleArray *res = new DoubleArray(rhs.size());
  for (size_t j = 0; j < lhs[0].size(); ++j) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      res[j] = res[j] + lhs[i][j] * rhs[j];
    }
  }
  return *res;
}

const DoubleMatrix &matrix_bultiply(const DoubleMatrix &lhs,
                                    const DoubleMatrix &rhs) {
  if ((lhs[0].size() != rhs.size())) {
    throw std::runtime_error("Dimensions have to be (m,n), (n,l)");
  }
  DoubleMatrix *res = new DoubleMatrix(lhs.size(), lhs[0].size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    for (size_t j = 0; j < lhs.size(); ++j) {
      for (size_t k = 0; k < lhs[0].size(); ++k) {
        res[i][j] = res[i][j] + lhs[i][k] * rhs[k][j];
      }
    }
  }
  return *res;
}
