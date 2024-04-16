//----
// @file Matrix.cpp
// @author mask <beloved25177@126.com>
// @brief 矩阵
// @version 1.0
// @date 2024-04-16
//
// @copyright Copyright (c) 2024
//
//----

#include <assert.h>
#include <iostream>

typedef unsigned short m_size_t;

template<typename T>
bool nearToZero(const T &val) {
  return val < 0.00001 && val > -0.00001;
}

template<typename T>
class Matrix {
  m_size_t row;
  m_size_t col;
  T **data;

public:
  Matrix(const m_size_t &_r, const m_size_t &_c) {
    data = new T *[_r];
    for (int i = 0; i < _r; ++i)
      data[i] = new T[_c];
    col = _c;
    row = _r;
  };
  ~Matrix() {
    for (int i = 0; i < row; ++i)
      delete[] data[i];
    delete[] data;
  }

  Matrix operator+(const Matrix<T> &_m) {
    assert(col == _m.col && row == _m.row);
    Matrix m = Matrix(row, col);
    for (int i = 0; i < row; ++i)
      for (int j = 0; j < col; ++j)
        m.data[i][j] = data[i][j] + _m.data[i][j];
    return m;
  }
  Matrix operator-(const Matrix<T> &_m) {
    assert(col == _m.col && row == _m.row);
    Matrix m = Matrix(row, col);
    for (int i = 0; i < row; ++i)
      for (int j = 0; j < col; ++j)
        m.data[i][j] = data[i][j] - _m.data[i][j];
    return m;
  }
  Matrix operator*(const Matrix<T> &_m) {
    assert(col == _m.row);
    Matrix m = Matrix(row, col);
    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j) {
        for (int k = 0; k < col; ++k) {
          m[i][j] += data[i][k] * _m[k][j];
        }
      }
    }
    return m;
  }
  Matrix trans() {
    Matrix m = Matrix(col, row);
    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j) {
        m.data[j][i] = data[i][j];
      }
    }
    return m;
  }

  void show() {
    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j)
        std::cout << data[i][j] << "\t";
      std::cout << std::endl;
    }
  }

  void gauss_inv() {
    assert(col == row);
    Matrix m = Matrix(row, (col << 1));
    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < (col << 1); ++j) {
        if (j < col)
          m.data[i][j] = data[i][j];
        else
          m.data[i][j] = (j - col == i) ? 1 : 0;
      }
    }
    m.show();
    for (int i = 0; i < row; ++i) {
      if (nearToZero(m.data[i][i])) {
        int j = i + 1;
        for (; j < col; ++j) {
          if (!nearToZero(m.data[i][j])) break;
        }
        if (j == col)
          return;
        for (int k = 0; k < (row << 1); ++k)
          m.data[i][k] += m.data[j][k];
      }
      float temp = m.data[i][i];
      for (int k = 0; k < 2 * row; ++k)
        m.data[i][k] /= temp;
      for (int j = i + 1; j < row; ++j) {
        temp = m.data[j][i];
        for (int k = i; k < (col << 1); ++k)
          m.data[j][k] -= temp * m.data[i][k];
      }
    }

    for (int i = row - 1; i >= 0; --i) {
      for (int j = i - 1; j >= 0; --j) {
        float temp = m.data[j][i];
        for (int k = i; k < (row << 1); ++k) {
          m.data[j][k] -= temp * m.data[i][k];
        }
      }
    }
    Matrix res = Matrix(row, col);
    for (int i = 0; i < row; ++i) {
      for (int j = row; j < (row << 1); ++j) {
        res.data[i][j - row] = m.data[i][j];
      }
    }
    res.show();
  }
  void set(const m_size_t &_i, const m_size_t &_j, const T &val) {
    data[_i][_j] = val;
  }
};

int main(int argc, char const *argv[]) {
  Matrix<float> m1(5, 5);
  float d[5][5] = {
    1,
    3,
    13,
    2,
    4,
    12,
    4,
    13,
    42,
    8,
    11,
    5,
    15,
    44,
    7,
    13,
    2,
    17,
    25,
    14,
    19,
    1,
    18,
    55,
    15,

  };
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; ++j) m1.set(i, j, d[i][j]);
  m1.show();
  m1.gauss_inv();
  return 0;
}
