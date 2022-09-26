#include <doublearray.hpp>

DoubleArray::DoubleArray() : _values(nullptr), _size(0) {}

DoubleArray::DoubleArray(const size_t size) : _values(nullptr), _size(size) {
  _values = new double[_size];
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

const DoubleArray DoubleArray::operator+=(const DoubleArray &rhs) {
  return (*this = *this + rhs);
}

const DoubleArray DoubleArray::operator-=(const DoubleArray &rhs) {
  return (*this = *this - rhs);
}

const DoubleArray DoubleArray::operator*=(const DoubleArray &rhs) {
  return (*this = *this * rhs);
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

const DoubleArray operator+(const DoubleArray &lhs, const DoubleArray &rhs) {
  if (lhs.size() != rhs.size()) {
    throw std::runtime_error("Dimensions have to be the same");
  }
  DoubleArray res = DoubleArray(lhs.size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    res[i] = lhs[i] + rhs[i];
  }
  return res;
}

const DoubleArray operator-(const DoubleArray &lhs, const DoubleArray &rhs) {
  if (lhs.size() != rhs.size()) {
    throw std::runtime_error("Dimensions have to be the same");
  }
  DoubleArray res = DoubleArray(lhs.size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    res[i] = lhs[i] - rhs[i];
  }
  return res;
}

const DoubleArray operator*(const DoubleArray &lhs, const DoubleArray &rhs) {
  if (lhs.size() != rhs.size()) {
    throw std::runtime_error("Dimensions have to be the same");
  }
  DoubleArray res = DoubleArray(lhs.size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    res[i] = lhs[i] * rhs[i];
  }
  return res;
}

const DoubleArray operator+(const DoubleArray &lhs, const double &rhs) {
  DoubleArray res = DoubleArray(lhs.size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    res[i] = lhs[i] + rhs;
  }
  return res;
}

const DoubleArray operator-(const DoubleArray &lhs, const double &rhs) {
  DoubleArray res = DoubleArray(lhs.size());
  for (size_t i = 0; i < lhs.size(); ++i) {
    res[i] = lhs[i] - rhs;
  }
  return res;
}
