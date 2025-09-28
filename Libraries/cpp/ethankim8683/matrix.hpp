#ifndef ETHANKIM8683_MATRIX
#define ETHANKIM8683_MATRIX 1

#include <assert.h>

#include <vector>

template <typename T>
struct mat {
 private:
  int n, m;
  std::vector<T> data;

 public:
  static mat identity(int n) {
    std::vector<T> rv(n * n);
    for (int i = 0; i < n; i++) {
      rv[i * n + i] = 1;
    }
    return mat(rv);
  }

  mat() {}
  mat(int n, int m) : n(n), m(m), data(n * m) {}
  mat(int n, int m, T val) : n(n), m(m), data(n * m, val) {}
  mat(const mat &rhs) : n(rhs.n), m(rhs.m), data(rhs.data) {}

  T* operator[](int i) { return &data[i * m]; }
  const T* operator[](int i) const { return &data[i * m]; }

  std::pair<int, int> dims() const { return {n, m}; }

  mat& operator+=(const mat& rhs) {
    for (int i = 0; i < data.size(); i++) {
      data[i] += rhs.data[i];
    }
    return *this;
  }

  mat& operator-=(const mat& rhs) {
    for (int i = 0; i < data.size(); i++) {
      data[i] -= rhs.data[i];
    }
    return *this;
  }

  mat& operator*=(const mat& rhs) {
    *this = *this * rhs;
    return *this;
  }
  
  mat operator+(const mat& rhs) const { return mat(*this) += rhs; }
  mat operator-(const mat& rhs) const { return mat(*this) -= rhs; }

  // https://en.algorithmica.org/hpc/algorithms/matmul/#transposition
  mat operator*(const mat &rhs) const {
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
    return mat(rv);
  }

  mat pow(int k) const {
    assert(0 <= k);
    assert(n == m);
    mat x = *this, rv = identity(n);
    while (k) {
        if (k & 1) rv *= x;
        x *= x;
        k >>= 1;
    }
    return rv;
  }

  mat transpose() const {
    std::vector<T> rv(n * m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        rv[j * n + i] = data[i * m + j];
      }
    }
    return mat(rv);
  }
};

#endif  // ETHANKIM8683_MATRIX