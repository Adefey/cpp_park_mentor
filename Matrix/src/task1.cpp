#include <task1.hpp>

DoubleArray::DoubleArray() : _values(nullptr), _size(0) {}

DoubleArray::DoubleArray(const size_t size) : _values(nullptr), _size(size) {
  _values = new double[size];
}

DoubleArray::DoubleArray(DoubleArray &value)
    : _values(nullptr), _size(value._size) {
  _values = new double[_size];
  for (size_t i = 0; i < _size; ++i) {
    _values[i] = value._values[i];
  }
}

DoubleArray::~DoubleArray() { delete[] _values; }

size_t DoubleArray::size() { return _size; }

double &DoubleArray::operator[](size_t index) { return _values[index]; }

DoubleArray::DoubleArray(std::initializer_list<double> l) {
  _size = l.size();
  size_t i = 0;
  for (auto it = l.begin(); it < l.end(); ++it) {
    _values[i++] = *it;
  }
}

DoubleMatrix::DoubleMatrix() : _values(nullptr), _size(0) {}

DoubleMatrix::DoubleMatrix(const size_t row_count, const size_t col_count)
    : _values(nullptr), _size(row_count) {
  _values = new DoubleArray[_size];
  for (size_t i = 0; i < row_count; ++i) {
    _values[i] = DoubleArray(row_count);
    for (size_t j = 0; j < col_count; ++j) {
      _values[i][j] = 0;
    }
  }
}

DoubleMatrix::DoubleMatrix(DoubleMatrix &value)
    : _values(nullptr), _size(value._size) {
  _values = new DoubleArray[value._size];
  for (size_t i = 0; i < value._size; ++i) {
    _values[i] = DoubleArray(value[i].size());
    for (size_t j = 0; j < value[i].size(); ++j) {
      _values[i][j] = value._values[i][j];
    }
  }
}
DoubleMatrix::~DoubleMatrix() { delete[] _values; }

size_t DoubleMatrix::size() { return _size; }

DoubleArray &DoubleMatrix::operator[](size_t index) { return _values[index]; }

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
  for (auto it = l.begin(); it < l.end(); ++it) {
    _values[i++] = *it;
  }
}
