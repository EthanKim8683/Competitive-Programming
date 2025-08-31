#ifndef ETHANKIM8683_COMBINATORICS
#define ETHANKIM8683_COMBINATORICS

#include <assert.h>

#include <array>
#include <type_traits>
#include <vector>

#include "ethankim8683/algebra.hpp"
#include "ethankim8683/type_traits.hpp"

template <typename T>
struct combinatorics_cache {
  inline static std::vector<T> fact = {1};

  static void reset() { fact = {1}; }
};

template <typename T, typename S,
          std::enable_if<std::is_integral<S>::value>::type * = nullptr>
T pow(T x, S y) {
  T rv = 1;
  for (; y; y >>= 1, x *= x) {
    if (y & 1) {
      rv *= x;
    }
  }
  return rv;
}

template <typename T>
T fact(int n) {
  if (n < 0) return 0;
  auto &fact = combinatorics_cache<T>::fact;
  while (!(n < fact.size())) {
    fact.push_back(fact.back() * fact.size());
  }
  return fact[n];
}

template <typename T>
T binom(int n, int k) {
  if (n < 0 or n - k < 0 or k < 0) return 0;
  return fact<T>(n) / (fact<T>(n - k) * fact<T>(k));
}

template <typename T, typename S,
          std::enable_if<std::is_integral<S>::value>::type * = nullptr>
T lucas_binom(S n, S k, unsigned mod) {
  using T2 = double_width<T>::type;

  if (n < 0 or k < 0) return 0;
  if (mod == 2) return (~n & k) == 0;

  assert(is_prime(mod));
  T rv = 1;
  while (n or k) {
    rv = (T2) rv * binom<T>(n % mod, k % mod) % mod;
    n /= mod;
    k /= mod;
  }
  return rv;
}

template <typename T>
T catalan(int n) {
  if (n < 0) return 0;
  return fact<T>(2 * n) / (fact<T>(n + 1) * fact<T>(n));
}
template <typename T>
T num_binary_trees(int n) {
  return catalan<T>(n);
}
template <typename T>
T num_full_binary_trees(int n) {
  if (n % 2 == 0) return 0;
  return catalan<T>(n / 2);
}
template <typename T>
T num_balanced_bracket_seqs(int n) {
  if (n % 2 == 1) return 0;
  return catalan<T>(n / 2);
}
template <typename T>
T num_triangulations(int n) {
  return catalan<T>(n - 2);
}

template <typename T>
T bertrand_ballot_thm(int p, int q) {
  if (p <= q) return 0;
  return T(p - q) / T(p + q);
}
template <typename T>
T bertrand_ballot_thm_with_ties(int p, int q) {
  if (p < q) return 0;
  return T(p + 1 - q) / T(p + 1);
}
// Number of balanced bracket sequences of length N composed of K non-composite
// bracket sequences
template <typename T>
T num_composite_balanced_bracket_seqs(int n, int k) {
  if (n % 2 == 1) return 0;
  return bertrand_ballot_thm<T>(n / 2, n / 2 - k) * binom<T>(n - k, n / 2);
}

#endif  // ETHANKIM8683_COMBINATORICS
