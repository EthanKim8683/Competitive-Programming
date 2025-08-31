#ifndef ETHANKIM8683_GEOMETRY
#define ETHANKIM8683_GEOMETRY

#include <complex>

// TODO: Implement a vector library

// https://codeforces.com/blog/entry/22175
template <typename T>
T dot(std::complex<T> a, std::complex<T> b) {
  return (std::conj(a) * b).real();
}
template <typename T>
T cross(std::complex<T> a, std::complex<T> b) {
  return (std::conj(a) * b).imag();
}
template <typename T>
T dist(std::complex<T> a, std::complex<T> b) {
  return std::norm(a - b);
}
template <typename T>
T comp(std::complex<T> a, std::complex<T> b) {
  return dot(a, b) / norm(b);
}
template <typename T>
std::complex<T> proj(std::complex<T> a, std::complex<T> b) {
  return b * dot(a, b) / dot(b, b);
}
template <typename T>
std::complex<T> rotate(std::complex<T> x, T theta) {
  return x * std::polar(T(1.0), theta);
}

// https://usaco.guide/plat/sweep-line#solution---seeing-the-boundary
// Sorts vectors by angle from positive x-axis; equivalent to arg(a) < arg(b)
template <typename T>
bool radial_cmp(std::complex<T> a, std::complex<T> b) {
  auto half = [&](std::complex<T> x) -> int {
    if (int rv = (x.imag() > 0) - (x.imag() < 0)) return rv;
    return (x.real() > 0) - (x.real() < 0);
  };
  if (int rv = half(a) - half(b)) return rv < 0;
  return cross(a, b) > 0;
}

#endif  // ETHANKIM8683_GEOMETRY
