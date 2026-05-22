#ifndef ETHANKIM8683_MATRIX
#define ETHANKIM8683_MATRIX 1

#include <cassert>
#include <vector>

namespace ethankim8683 {

template <class T>
std::vector<std::vector<T>> matmul(const std::vector<std::vector<T>> &a,
                                   const std::vector<std::vector<T>> &b) {
  assert(a[0].size() == b.size());
  std::vector rv(a.size(), std::vector<T>(b[0].size(), 0));
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < b[0].size(); j++) {
      for (int k = 0; k < a[0].size(); k++) {
        rv[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return rv;
}

template <class T>
std::vector<std::vector<T>> pow(std::vector<std::vector<T>> x, long long y) {
  assert(y >= 0);
  assert(x.size() == x[0].size());
  std::vector rv(x.size(), std::vector<T>(x.size(), 0));
  for (int i = 0; i < x.size(); i++) {
    rv[i][i] = 1;
  }
  for (; y; y >>= 1, x = matmul(x, x)) {
    if (y & 1) {
      rv = matmul(x, rv);
    }
  }
  return rv;
}

// TODO: Implement matrix inverse
// template <class T>
// std::vector<std::vector<T>> inv(std::vector<std::vector<T>> x) {}

}  // namespace ethankim8683

#endif  // ETHANKIM8683_MATRIX
