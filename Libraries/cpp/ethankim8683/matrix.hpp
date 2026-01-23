#ifndef ETHANKIM8683_MATRIX
#define ETHANKIM8683_MATRIX 1

#include <assert.h>

#include <vector>

// TODO: Implement matrix inverse
template <typename T>
struct matrix {
 private:
  int n, m;
  std::vector<T> data;

 public:
  static matrix id(int n) {
    std::vector<T> rv(n * n);
    for (int i = 0; i < n; i++) {
      rv[i * n + i] = 1;
    }
    return matrix(rv);
  }

  matrix() {}
  matrix(int n, int m) : n(n), m(m), data(n * m) {}
  matrix(int n, int m, T val) : n(n), m(m), data(n * m, val) {}
  matrix(const matrix &rhs) : n(rhs.n), m(rhs.m), data(rhs.data) {}

  T *operator[](int i) { return &data[i * m]; }
  const T *operator[](int i) const { return &data[i * m]; }

  std::pair<int, int> dims() const { return {n, m}; }

  matrix &operator+=(const matrix &rhs) {
    for (int i = 0; i < data.size(); i++) {
      data[i] += rhs.data[i];
    }
    return *this;
  }

  matrix &operator-=(const matrix &rhs) {
    for (int i = 0; i < data.size(); i++) {
      data[i] -= rhs.data[i];
    }
    return *this;
  }

  matrix &operator*=(const matrix &rhs) {
    *this = *this * rhs;
    return *this;
  }

  matrix operator+(const matrix &rhs) const { return matrix(*this) += rhs; }
  matrix operator-(const matrix &rhs) const { return matrix(*this) -= rhs; }

  // https://en.algorithmica.org/hpc/algorithms/matmul/#transposition
  matrix operator*(const matrix &rhs) const {
    assert(m == rhs.n);
    std::vector<T> rhs_t(rhs.data.size());
    for (int i = 0; i < rhs.n; i++) {
      for (int j = 0; j < rhs.m; j++) {
        rhs_t[j * rhs.n + i] = rhs.data[i * rhs.m + j];
      }
    }
    std::vector<T> rv(n * rhs.m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < rhs.m; j++) {
        for (int k = 0; k < m; k++) {
          rv[i * rhs.m + j] += data[i * m + k] * rhs_t[j * rhs.n + k];
        }
      }
    }
    return matrix(rv);
  }

  matrix pow(int k) const {
    assert(0 <= k);
    assert(n == m);
    matrix x = *this, rv = id(n);
    while (k) {
      if (k & 1) rv *= x;
      x *= x;
      k >>= 1;
    }
    return rv;
  }

  matrix trans() const {
    std::vector<T> rv(n * m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        rv[j * n + i] = data[i * m + j];
      }
    }
    return matrix(rv);
  }
};

#endif  // ETHANKIM8683_MATRIX
