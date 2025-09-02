#ifndef ETHANKIM8683_MATRIX
#define ETHANKIM8683_MATRIX 1

#include <vector>

template <typename T>
struct mat {
 private:
  std::vector<std::vector<T>> data;
};

#endif  // ETHANKIM8683_MATRIX