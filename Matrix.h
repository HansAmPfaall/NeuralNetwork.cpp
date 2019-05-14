#pragma once
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

class Matrix {
 public:
  // ___________________________________________________________________________
  // Constructor for Matrix with random values.
  Matrix(int rows, int cols) {
    _rowNum = rows;
    _colNum = cols;
    _storage.resize(rows * cols);
    for (int i = 0; i < rows * cols; i++) {
      _storage[i] =
          2 * (((double)rand() / RAND_MAX) - ((double)rand() / RAND_MAX));
          // std::cout << _storage[i] << std::endl;
    }
  }

  // ___________________________________________________________________________
  // Constructor.
  Matrix(int rows, int cols, float value) {
    _rowNum = rows;
    _colNum = cols;
    _storage.resize(rows * cols);
    for (int i = 0; i < rows * cols; i++) {
      _storage[i] = value;
    }
  }

  // ___________________________________________________________________________
  // Constructor.
  Matrix(int rows, int cols, std::vector<float> &values) {
    _rowNum = rows;
    _colNum = cols;
    _storage.resize(rows * cols);
    for (int i = 0; i < rows * cols; i++) {
      _storage[i] = values[i];
    }
  }

  // Matrix(const Matrix &m)
  // {
  // copy constructor
  // }

  // ___________________________________________________________________________
  // Destructor.
  ~Matrix() {}

  // ___________________________________________________________________________
  // Print the Matrix.
  void print() {
    for (int i = 0; i < _rowNum * _colNum; i++) {
      if (i % _colNum == 0 && i > 0) {
        std::cout << std::endl;
      }
      std::cout << _storage[i] << " ";
    }
    std::cout << std::endl;
  }

  void mult(float value) {
    for (int i = 0; i < _colNum * _rowNum; i++) {
      _storage[i] *= value;
    }
  }

  // ___________________________________________________________________________
  // Matrixmultiplication, return the product.
  Matrix mult(const Matrix &m) const {
    assert(_colNum == m._rowNum);
    Matrix temp(_rowNum, m._colNum, 0);
    for (int i = 0; i < _rowNum; i++) {
      for (int k = 0; k < m._colNum; k++) {
        for (int j = 0; j < _colNum; j++) {
          temp._storage[i * temp._colNum + k] +=
              _storage[i * _colNum + j] * m._storage[j * m._colNum + k];
        }
      }
    }
    return temp;
  }

  // ___________________________________________________________________________
  Matrix operator*(Matrix &m) { return mult(m); }

  // ___________________________________________________________________________
  // A Setter Function.
  void setValue(int row, int col, float value) {
    assert(row < _rowNum && col < _colNum);
    _storage[_colNum * row + col] = value;
  }

  // ___________________________________________________________________________
  // A Getter Function.
  float getValue(int row, int col) {
    assert(row < _rowNum && col < _colNum);
    return _storage[_colNum * row + col];
  }

  // ___________________________________________________________________________
  // Add a Value to every entry in the Matrix.
  void add(float x) {
    for (int i = 0; i < _rowNum * _colNum; i++) {
      _storage[i] += x;
    }
  }

  std::vector<float> normalize() {
    std::vector<float> temp;
    temp.resize(_rowNum * _colNum);
    float size = 0.0;
    for (int i = 0; i < _rowNum * _colNum; i++) {
      size += _storage[i];
    }
    for (int i = 0; i < _rowNum * _colNum; i++) {
      temp[i] = _storage[i] / size;
    }
    return temp;
  }

  void mutate() {
    for (int i = 0; i < _rowNum * _colNum; i++) {
      _storage[i] += _storage[i] * 2;
    }
  }

  std::vector<float> toVector() {
    std::vector<float> temp;
    temp.resize(_rowNum * _colNum);
    for (int i = 0; i < _rowNum * _colNum; i++) {
      temp[i] = _storage[i];
    }
    return temp;
  }

  // ___________________________________________________________________________
  // Add one Matrix to another.
  void add(const Matrix &m) {
    assert(_rowNum == m._rowNum && _colNum == m._colNum);
    for (int i = 0; i < _rowNum * _colNum; i++) {
      _storage[i] += m._storage[i];
    }
  }

  Matrix operator+(const Matrix &m) const {
    Matrix result = *this;
    result += m;
    return result;
  }

  void operator+=(const Matrix &m) { add(m); }

  void sub(const Matrix &m) {
    assert(_rowNum == m._rowNum && _colNum == m._colNum);
    for (int i = 0; i < _rowNum * _colNum; i++) {
      _storage[i] -= m._storage[i];
    }
  }

  Matrix operator-(const Matrix &m) const {
    Matrix result = *this;
    result -= m;
    return result;
  }

  void operator-=(const Matrix &m) { sub(m); }

  // ___________________________________________________________________________
  void operator+(float value) {
    for (int i = 0; i < _rowNum * _colNum; i++) {
      _storage[i] += value;
    }
  }

  // ___________________________________________________________________________
  // Transpose the Matrix.
  Matrix t() {
    Matrix temp(_colNum, _rowNum, 0);
    for (int i = 0; i < _colNum * _rowNum; i++) {
      temp.setValue(i % _colNum, i / _colNum, _storage[i]);
    }
    return temp;
  }

  // ___________________________________________________________________________
  // Applies the sigmoid function.
  void sigmoid() {
    for (int i = 0; i < _rowNum * _colNum; i++) {
      _storage[i] = 1 / (1 + exp(-_storage[i]));
    }
  }

  Matrix sigmoid_r() {
    Matrix temp(_rowNum, _colNum, 0);
    for (int i = 0; i < _rowNum * _colNum; i++) {
      temp._storage[i] = 1 / (1 + exp(-_storage[i]));
    }
    return temp;
  }

  // ___________________________________________________________________________
  // Applies the Derivative of the sigmoid function.
  void d_sigmoid() {
    for (int i = 0; i < _rowNum * _colNum; i++) {
      _storage[i] = pow(exp(-_storage[i]) / (1 + exp(-_storage[i])), 2);
    }
  }

  // ___________________________________________________________________________
  // Applies the Derivative of the sigmoid function.
  Matrix d_sigmoid_r() {
    Matrix temp(_rowNum, _colNum, 0);
    for (int i = 0; i < _rowNum * _colNum; i++) {
      temp._storage[i] = pow(exp(-_storage[i]) / (1 + exp(-_storage[i])), 2);
    }
    return temp;
  }

  // The Rows of the Matrix.
  int _rowNum;

  // The Collums of the Matrix.
  int _colNum;
  // The Entries of the Matrix.
  std::vector<float> _storage;
};