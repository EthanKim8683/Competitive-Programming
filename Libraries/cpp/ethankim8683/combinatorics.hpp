#ifndef ETHANKIM8683_COMBINATORICS
#define ETHANKIM8683_COMBINATORICS 1

#include <cassert>
#include <type_traits>
#include <vector>

#include "ethankim8683/algebra"
#include "ethankim8683/type_traits"

namespace ethankim8683 {

template <class T>
struct combinatorics_cache {
  inline static std::vector<T> fact = {1};
  inline static std::vector<T> inv_fact = {1};

  static void reset() {
    fact = {1};
    inv_fact = {1};
  }
};

template <class T>
T pow(T x, long long y) {
  assert(y >= 0);
  T rv = 1;
  for (; y; y >>= 1, x *= x) {
    if (y & 1) {
      rv *= x;
    }
  }
  return rv;
}

template <class T>
T fact(int n) {
  assert(n >= 0);
  auto &fact = combinatorics_cache<T>::fact;
  while (!(n < (int) fact.size())) {
    fact.push_back(fact.back() * fact.size());
  }
  return fact[n];
}

template <class T, std::enable_if_t<is_invertible_v<T>> * = nullptr>
T inv_fact(int n) {
  assert(n >= 0);
  auto &inv_fact = combinatorics_cache<T>::inv_fact;
  while (!(n < (int) inv_fact.size())) {
    inv_fact.push_back(inv_fact.back() / inv_fact.size());
  }
  return inv_fact[n];
}

template <class T>
T binom(int n, int k) {
  if (n < 0 or n - k < 0 or k < 0) return 0;
  if constexpr (is_invertible_v<T>) {
    return fact<T>(n) * inv_fact<T>(n - k) * inv_fact<T>(k);
  } else {
    return fact<T>(n) / (fact<T>(n - k) * fact<T>(k));
  }
}

template <class T>
T lucas_binom(long long n, long long k, int mod) {
  using T2 = double_width_t<T>;

  assert(mod > 0);
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

template <class T>
T catalan(int n) {
  if (n < 0) return 0;
  if constexpr (is_invertible_v<T>) {
    return fact<T>(2 * n) * inv_fact<T>(n + 1) * inv_fact<T>(n);
  } else {
    return fact<T>(2 * n) / (fact<T>(n + 1) * fact<T>(n));
  }
}
template <class T>
T num_binary_trees(int n) {
  return catalan<T>(n);
}
template <class T>
T num_full_binary_trees(int n) {
  if (n % 2 == 0) return 0;
  return catalan<T>(n / 2);
}
template <class T>
T num_balanced_bracket_seqs(int n) {
  if (n % 2 == 1) return 0;
  return catalan<T>(n / 2);
}
template <class T>
T num_triangulations(int n) {
  return catalan<T>(n - 2);
}

template <class T>
T bertrand_ballot_thm(long long p, long long q) {
  assert(p >= 0);
  assert(q >= 0);
  if (p <= q) return 0;
  return T(p - q) / T(p + q);
}
template <class T>
T bertrand_ballot_thm_with_ties(long long p, long long q) {
  assert(p >= 0);
  assert(q >= 0);
  if (p < q) return 0;
  return T(p + 1 - q) / T(p + 1);
}
// Number of balanced bracket sequences of length N composed of K non-composite
// bracket sequences
template <class T>
T num_composite_balanced_bracket_seqs(int n, int k) {
  if (n % 2 == 1) return 0;
  return bertrand_ballot_thm<T>(n / 2, n / 2 - k) * binom<T>(n - k, n / 2);
}

}  // namespace ethankim8683

#endif  // ETHANKIM8683_COMBINATORICS
