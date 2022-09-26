#include <doublematrix.hpp>
#include <iostream>

DoubleMatrix::DoubleMatrix() : _values(nullptr), _size(0) {}

DoubleMatrix::DoubleMatrix(const size_t row_count, const size_t col_count)
    : _values(nullptr), _size(row_count) {
  _values = new DoubleArray[_size];
  for (size_t i = 0; i < row_count; ++i) {
    _values[i] = *(new DoubleArray(col_count));
    for (size_t j = 0; j < col_count; ++j) { // NOLINT
      _values[i][j] = 0;
    }
  }
}

DoubleMatrix::DoubleMatrix(DoubleMatrix &value)
    : _values(nullptr), _size(value._size) {
  _values = new DoubleArray[value._size];
  for (size_t i = 0; i < value._size; ++i) {
    _values[i] = *(new DoubleArray(value[i].size()));
    for (size_t j = 0; j < value[i].size(); ++j) { // NOLINT
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
  if (index >= _size) {
    throw std::runtime_error("Index out of bounds");
  }
  DoubleArray res(_values[index]);
  return res;
}

DoubleArray DoubleMatrix::get_col(size_t index) {
  if (index >= _values[0].size()) {
    throw std::runtime_error("Index out of bounds");
  }
  DoubleArray res(_size);
  for (size_t i = 0; i < _size; ++i) {
    res[i] = _values[i][index];
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

DoubleMatrix::DoubleMatrix(
    std::initializer_list<std::initializer_list<double>> l) {
  _size = l.size();
  _values = new DoubleArray[_size];
  size_t i = 0;
  for (std::initializer_list<double> e : l) { // NOLINT
    _values[i++] = *(new DoubleArray(e));
  }
}

const DoubleMatrix DoubleMatrix::operator+=(const DoubleMatrix &rhs) {
  return (*this = *this + rhs);
}
const DoubleMatrix DoubleMatrix::operator-=(const DoubleMatrix &rhs) {
  return (*this = *this - rhs);
}
const DoubleMatrix DoubleMatrix::operator*=(const DoubleMatrix &rhs) {
  return (*this = *this * rhs);
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

const DoubleMatrix operator+(const DoubleMatrix &lhs, const DoubleMatrix &rhs) {
  if ((lhs.size() != rhs.size()) || (lhs[0].size() != rhs[0].size())) {
    throw std::runtime_error("Dimensions have to be the same");
  }
  DoubleMatrix res = DoubleMatrix(lhs.size(), lhs[0].size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    for (size_t j = 0; j < lhs[0].size(); ++j) {
      res[i][j] = lhs[i][j] + rhs[i][j];
    }
  }
  return res;
}

const DoubleMatrix operator-(const DoubleMatrix &lhs, const DoubleMatrix &rhs) {

  if ((lhs.size() != rhs.size()) || (lhs[0].size() != rhs[0].size())) {
    throw std::runtime_error("Dimensions have to be the same");
  }
  DoubleMatrix res = DoubleMatrix(lhs.size(), lhs[0].size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    for (size_t j = 0; j < lhs[0].size(); ++j) {
      res[i][j] = lhs[i][j] - rhs[i][j];
    }
  }
  return res;
}

const DoubleMatrix operator*(const DoubleMatrix &lhs, const DoubleMatrix &rhs) {

  if ((lhs.size() != rhs.size()) || (lhs[0].size() != rhs[0].size())) {
    throw std::runtime_error("Dimensions have to be the same");
  }
  DoubleMatrix res = DoubleMatrix(lhs.size(), lhs[0].size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    for (size_t j = 0; j < lhs[0].size(); ++j) {
      res[i][j] = lhs[i][j] * rhs[i][j];
    }
  }
  return res;
}

const DoubleMatrix operator*(const double &lhs, const DoubleMatrix &rhs) {
  DoubleMatrix res = DoubleMatrix(rhs.size(), rhs[0].size());
  for (size_t i = 0; i < rhs.size(); ++i) {
    for (size_t j = 0; j < rhs[0].size(); ++j) {
      res[i][j] = rhs[i][j] * lhs;
    }
  }
  return res;
}
const DoubleArray operator*(const DoubleArray &lhs, const DoubleMatrix &rhs) {
  if ((lhs.size() != rhs[0].size())) {
    throw std::runtime_error("Dimensions have to be (m), (n,m)");
  }
  DoubleArray res = DoubleArray(lhs.size());
  for (size_t j = 0; j < rhs[0].size(); ++j) {
    for (size_t i = 0; i < rhs.size(); ++i) {
      res[j] += lhs[i] * rhs[i][j];
    }
  }
  return res;
}
const DoubleArray operator*(const DoubleMatrix &lhs, const DoubleArray &rhs) {
  if ((rhs.size() != lhs[0].size())) {
    throw std::runtime_error("Dimensions have to be (m), (n,m)");
  }
  DoubleArray res = DoubleArray(rhs.size());
  for (size_t i = 0; i < lhs[0].size(); ++i) {
    for (size_t j = 0; j < lhs.size(); ++j) {
      res[i] += lhs[i][j] * rhs[j];
    }
  }
  return res;
}

const DoubleMatrix matrix_multiply(const DoubleMatrix &lhs,
                                   const DoubleMatrix &rhs) {
  if ((lhs[0].size() != rhs.size())) {
    throw std::runtime_error("Dimensions have to be (m,n), (n,l)");
  }
  DoubleMatrix res = DoubleMatrix(lhs.size(), lhs[0].size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    for (size_t j = 0; j < lhs.size(); ++j) {
      for (size_t k = 0; k < lhs[0].size(); ++k) {
        res[i][j] = res[i][j] + lhs[i][k] * rhs[k][j];
      }
    }
  }
  return res;
}

/* 5) */
const DoubleMatrix operator+(const DoubleMatrix &lhs, const double &rhs) {
  DoubleMatrix res = DoubleMatrix(lhs.size(), lhs[0].size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    for (size_t j = 0; j < lhs.size(); ++j) {
      res[i][j] = lhs[i][j] + rhs;
    }
  }
  return res;
}
const DoubleMatrix operator-(const DoubleMatrix &lhs, const double &rhs) {
  DoubleMatrix res = DoubleMatrix(lhs.size(), lhs[0].size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    for (size_t j = 0; j < lhs.size(); ++j) {
      res[i][j] = lhs[i][j] - rhs;
    }
  }
  return res;
}

const DoubleMatrix add_arr_to_matrix(DoubleMatrix &lhs, DoubleArray &rhs,
                                     size_t ind, bool is_row) {
  if (is_row) {
    if (lhs[ind].size() != rhs.size()) {
      throw std::runtime_error(
          "Dimensions have to be equal for row and vector");
    }
    DoubleMatrix res = lhs;
    for (size_t i = 0; i < rhs.size(); ++i) {
      res[ind][i] += rhs[i];
    }
    return res;
  } else {
    if (lhs.size() != rhs.size()) {
      throw std::runtime_error(
          "Dimensions have to be equal for col and vector");
    }
    DoubleMatrix res = lhs;
    for (size_t i = 0; i < rhs.size(); ++i) {
      res[i][ind] += rhs[i];
    }
    return res;
  }
  throw std::runtime_error("Something went wrong");
}
const DoubleMatrix substract_arr_from_matrix(DoubleMatrix &lhs,
                                             DoubleArray &rhs, size_t ind,
                                             bool is_row) {
  if (is_row) {
    if (lhs[ind].size() != rhs.size()) {
      throw std::runtime_error(
          "Dimensions have to be equal for row and vector");
    }
    DoubleMatrix res = lhs;
    for (size_t i = 0; i < rhs.size(); ++i) {
      res[ind][i] -= rhs[i];
    }
    return res;
  } else {
    if (lhs.size() != rhs.size()) {
      throw std::runtime_error(
          "Dimensions have to be equal for col and vector");
    }
    DoubleMatrix res = lhs;
    for (size_t i = 0; i < rhs.size(); ++i) {
      res[i][ind] -= rhs[i];
    }
    return res;
  }
  throw std::runtime_error("Something went wrong");
}

const DoubleMatrix DoubleMatrix::transpose() {
  DoubleMatrix res = DoubleMatrix(_values[0].size(), _size);
  for (size_t i = 0; i < _size; ++i) {
    for (size_t j = 0; j < _values[0].size(); ++j) {
      res[j][i] = (*this)[i][j];
    }
  }
  return res;
}
const DoubleMatrix DoubleMatrix::inverse() {
  if ((*this)[0].size() != (*this).size()) {
    throw std::runtime_error("Dimensions have to be the same");
  }
  DoubleMatrix res = DoubleMatrix(_size, _size);
  if ((*this).size() == 1) {
    res[0][0] = (*this)[0][0];
  } else if ((*this).size() == 2) {
    double inv_det =
        1 / ((*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0]);
    res[0][0] = inv_det * (*this)[1][1];
    res[0][1] = -inv_det * (*this)[0][1];
    res[1][0] = -inv_det * (*this)[1][0];
    res[1][1] = inv_det * (*this)[0][0];
  } else if ((*this).size() == 3) {
    throw std::runtime_error("Not implemented");
  } else {
    throw std::runtime_error("Not implemented");
  }
  return res;
}

const DoubleMatrix DoubleMatrix::get_minor(size_t row, size_t col) {
  throw std::runtime_error("Not implemented");
}

const double DoubleMatrix::get_determinant() {
  if ((*this)[0].size() != (*this).size()) {
    throw std::runtime_error("Dimensions have to be the same");
  }
  double res = 0;
  size_t d = 1;
  if ((*this).size() == 1) {
    res = (*this)[0][0];
  } else if ((*this).size() == 2) {
    res = (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
  } else if ((*this).size() == 3) {
    res = (*this)[0][0] * (*this)[1][1] * (*this)[2][2] +
          (*this)[0][1] * (*this)[1][2] * (*this)[2][0] +
          (*this)[0][2] * (*this)[1][0] * (*this)[2][1] -
          (*this)[0][2] * (*this)[1][1] * (*this)[2][0] -
          (*this)[0][1] * (*this)[1][0] * (*this)[2][2] -
          (*this)[0][0] * (*this)[1][2] * (*this)[2][1];
  } else {
    throw std::runtime_error("Not implemented");
  }
  return res;
}
