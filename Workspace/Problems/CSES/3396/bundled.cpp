#ifndef ATCODER_INTERNAL_TYPE_TRAITS_HPP
#define ATCODER_INTERNAL_TYPE_TRAITS_HPP 1

#include <cassert>
#include <numeric>
#include <type_traits>

namespace atcoder {

namespace internal {

#ifndef _MSC_VER
template <class T>
using is_signed_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value ||
                                  std::is_same<T, __int128>::value,
                              std::true_type, std::false_type>::type;

template <class T>
using is_unsigned_int128 =
    typename std::conditional<std::is_same<T, __uint128_t>::value ||
                                  std::is_same<T, unsigned __int128>::value,
                              std::true_type, std::false_type>::type;

template <class T>
using make_unsigned_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value, __uint128_t,
                              unsigned __int128>;

template <class T>
using is_integral =
    typename std::conditional<std::is_integral<T>::value ||
                                  is_signed_int128<T>::value ||
                                  is_unsigned_int128<T>::value,
                              std::true_type, std::false_type>::type;

template <class T>
using is_signed_int =
    typename std::conditional<(is_integral<T>::value &&
                               std::is_signed<T>::value) ||
                                  is_signed_int128<T>::value,
                              std::true_type, std::false_type>::type;

template <class T>
using is_unsigned_int =
    typename std::conditional<(is_integral<T>::value &&
                               std::is_unsigned<T>::value) ||
                                  is_unsigned_int128<T>::value,
                              std::true_type, std::false_type>::type;

template <class T>
using to_unsigned = typename std::conditional<
    is_signed_int128<T>::value, make_unsigned_int128<T>,
    typename std::conditional<std::is_signed<T>::value, std::make_unsigned<T>,
                              std::common_type<T>>::type>::type;

#else

template <class T>
using is_integral = typename std::is_integral<T>;

template <class T>
using is_signed_int =
    typename std::conditional<is_integral<T>::value && std::is_signed<T>::value,
                              std::true_type, std::false_type>::type;

template <class T>
using is_unsigned_int =
    typename std::conditional<is_integral<T>::value &&
                                  std::is_unsigned<T>::value,
                              std::true_type, std::false_type>::type;

template <class T>
using to_unsigned =
    typename std::conditional<is_signed_int<T>::value, std::make_unsigned<T>,
                              std::common_type<T>>::type;

#endif

template <class T>
using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

template <class T>
using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

template <class T>
using to_unsigned_t = typename to_unsigned<T>::type;

}  // namespace internal

}  // namespace atcoder

#endif  // ATCODER_INTERNAL_TYPE_TRAITS_HPP

// #include "atcoder/internal_type_traits.hpp"

#ifndef ATCODER_INTERNAL_MATH_HPP
#define ATCODER_INTERNAL_MATH_HPP 1

#include <utility>

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace atcoder {

namespace internal {

// @param m `1 <= m`
// @return x mod m
constexpr long long safe_mod(long long x, long long m) {
  x %= m;
  if (x < 0) x += m;
  return x;
}

// Fast modular multiplication by barrett reduction
// Reference: https://en.wikipedia.org/wiki/Barrett_reduction
// NOTE: reconsider after Ice Lake
struct barrett {
  unsigned int _m;
  unsigned long long im;

  // @param m `1 <= m`
  explicit barrett(unsigned int m)
      : _m(m), im((unsigned long long) (-1) / m + 1) {}

  // @return m
  unsigned int umod() const { return _m; }

  // @param a `0 <= a < m`
  // @param b `0 <= b < m`
  // @return `a * b % m`
  unsigned int mul(unsigned int a, unsigned int b) const {
    // [1] m = 1
    // a = b = im = 0, so okay

    // [2] m >= 2
    // im = ceil(2^64 / m)
    // -> im * m = 2^64 + r (0 <= r < m)
    // let z = a*b = c*m + d (0 <= c, d < m)
    // a*b * im = (c*m + d) * im = c*(im*m) + d*im = c*2^64 + c*r + d*im
    // c*r + d*im < m * m + m * im < m * m + 2^64 + m <= 2^64 + m * (m + 1) <
    // 2^64 * 2
    // ((ab * im) >> 64) == c or c + 1
    unsigned long long z = a;
    z *= b;
#ifdef _MSC_VER
    unsigned long long x;
    _umul128(z, im, &x);
#else
    unsigned long long x =
        (unsigned long long) (((unsigned __int128) (z) *im) >> 64);
#endif
    unsigned long long y = x * _m;
    return (unsigned int) (z - y + (z < y ? _m : 0));
  }
};

// @param n `0 <= n`
// @param m `1 <= m`
// @return `(x ** n) % m`
constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
  if (m == 1) return 0;
  unsigned int _m = (unsigned int) (m);
  unsigned long long r = 1;
  unsigned long long y = safe_mod(x, m);
  while (n) {
    if (n & 1) r = (r * y) % _m;
    y = (y * y) % _m;
    n >>= 1;
  }
  return r;
}

// Reference:
// M. Forisek and J. Jancina,
// Fast Primality Testing for Integers That Fit into a Machine Word
// @param n `0 <= n`
constexpr bool is_prime_constexpr(int n) {
  if (n <= 1) return false;
  if (n == 2 || n == 7 || n == 61) return true;
  if (n % 2 == 0) return false;
  long long d = n - 1;
  while (d % 2 == 0) d /= 2;
  constexpr long long bases[3] = {2, 7, 61};
  for (long long a : bases) {
    long long t = d;
    long long y = pow_mod_constexpr(a, t, n);
    while (t != n - 1 && y != 1 && y != n - 1) {
      y = y * y % n;
      t <<= 1;
    }
    if (y != n - 1 && t % 2 == 0) {
      return false;
    }
  }
  return true;
}
template <int n>
constexpr bool is_prime = is_prime_constexpr(n);

// @param b `1 <= b`
// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
  a = safe_mod(a, b);
  if (a == 0) return {b, 0};

  // Contracts:
  // [1] s - m0 * a = 0 (mod b)
  // [2] t - m1 * a = 0 (mod b)
  // [3] s * |m1| + t * |m0| <= b
  long long s = b, t = a;
  long long m0 = 0, m1 = 1;

  while (t) {
    long long u = s / t;
    s -= t * u;
    m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b

    // [3]:
    // (s - t * u) * |m1| + t * |m0 - m1 * u|
    // <= s * |m1| - t * u * |m1| + t * (|m0| + |m1| * u)
    // = s * |m1| + t * |m0| <= b

    auto tmp = s;
    s = t;
    t = tmp;
    tmp = m0;
    m0 = m1;
    m1 = tmp;
  }
  // by [3]: |m0| <= b/g
  // by g != b: |m0| < b/g
  if (m0 < 0) m0 += b / s;
  return {s, m0};
}

// Compile time primitive root
// @param m must be prime
// @return primitive root (and minimum in now)
constexpr int primitive_root_constexpr(int m) {
  if (m == 2) return 1;
  if (m == 167772161) return 3;
  if (m == 469762049) return 3;
  if (m == 754974721) return 11;
  if (m == 998244353) return 3;
  int divs[20] = {};
  divs[0] = 2;
  int cnt = 1;
  int x = (m - 1) / 2;
  while (x % 2 == 0) x /= 2;
  for (int i = 3; (long long) (i) *i <= x; i += 2) {
    if (x % i == 0) {
      divs[cnt++] = i;
      while (x % i == 0) {
        x /= i;
      }
    }
  }
  if (x > 1) {
    divs[cnt++] = x;
  }
  for (int g = 2;; g++) {
    bool ok = true;
    for (int i = 0; i < cnt; i++) {
      if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) return g;
  }
}
template <int m>
constexpr int primitive_root = primitive_root_constexpr(m);

// @param n `n < 2^32`
// @param m `1 <= m < 2^32`
// @return sum_{i=0}^{n-1} floor((ai + b) / m) (mod 2^64)
unsigned long long floor_sum_unsigned(unsigned long long n,
                                      unsigned long long m,
                                      unsigned long long a,
                                      unsigned long long b) {
  unsigned long long ans = 0;
  while (true) {
    if (a >= m) {
      ans += n * (n - 1) / 2 * (a / m);
      a %= m;
    }
    if (b >= m) {
      ans += n * (b / m);
      b %= m;
    }

    unsigned long long y_max = a * n + b;
    if (y_max < m) break;
    // y_max < m * (n + 1)
    // floor(y_max / m) <= n
    n = (unsigned long long) (y_max / m);
    b = (unsigned long long) (y_max % m);
    std::swap(m, a);
  }
  return ans;
}

}  // namespace internal

}  // namespace atcoder

#endif  // ATCODER_INTERNAL_MATH_HPP

// #include "atcoder/internal_math.hpp"

#ifndef ATCODER_MODINT_HPP
#define ATCODER_MODINT_HPP 1

#include <cassert>
#include <numeric>
#include <type_traits>

#ifdef _MSC_VER
#include <intrin.h>
#endif

// #include "atcoder/internal_math"
// #include "atcoder/internal_type_traits"

namespace atcoder {

namespace internal {

struct modint_base {};
struct static_modint_base : modint_base {};

template <class T>
using is_modint = std::is_base_of<modint_base, T>;
template <class T>
using is_modint_t = std::enable_if_t<is_modint<T>::value>;

}  // namespace internal

template <int m, std::enable_if_t<(1 <= m)> * = nullptr>
struct static_modint : internal::static_modint_base {
  using mint = static_modint;

 public:
  static constexpr int mod() { return m; }
  static mint raw(int v) {
    mint x;
    x._v = v;
    return x;
  }

  static_modint() : _v(0) {}
  template <class T, internal::is_signed_int_t<T> * = nullptr>
  static_modint(T v) {
    long long x = (long long) (v % (long long) (umod()));
    if (x < 0) x += umod();
    _v = (unsigned int) (x);
  }
  template <class T, internal::is_unsigned_int_t<T> * = nullptr>
  static_modint(T v) {
    _v = (unsigned int) (v % umod());
  }

  unsigned int val() const { return _v; }

  mint &operator++() {
    _v++;
    if (_v == umod()) _v = 0;
    return *this;
  }
  mint &operator--() {
    if (_v == 0) _v = umod();
    _v--;
    return *this;
  }
  mint operator++(int) {
    mint result = *this;
    ++*this;
    return result;
  }
  mint operator--(int) {
    mint result = *this;
    --*this;
    return result;
  }

  mint &operator+=(const mint &rhs) {
    _v += rhs._v;
    if (_v >= umod()) _v -= umod();
    return *this;
  }
  mint &operator-=(const mint &rhs) {
    _v -= rhs._v;
    if (_v >= umod()) _v += umod();
    return *this;
  }
  mint &operator*=(const mint &rhs) {
    unsigned long long z = _v;
    z *= rhs._v;
    _v = (unsigned int) (z % umod());
    return *this;
  }
  mint &operator/=(const mint &rhs) { return *this = *this * rhs.inv(); }

  mint operator+() const { return *this; }
  mint operator-() const { return mint() - *this; }

  mint pow(long long n) const {
    assert(0 <= n);
    mint x = *this, r = 1;
    while (n) {
      if (n & 1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  mint inv() const {
    if (prime) {
      assert(_v);
      return pow(umod() - 2);
    } else {
      auto eg = internal::inv_gcd(_v, m);
      assert(eg.first == 1);
      return eg.second;
    }
  }

  friend mint operator+(const mint &lhs, const mint &rhs) {
    return mint(lhs) += rhs;
  }
  friend mint operator-(const mint &lhs, const mint &rhs) {
    return mint(lhs) -= rhs;
  }
  friend mint operator*(const mint &lhs, const mint &rhs) {
    return mint(lhs) *= rhs;
  }
  friend mint operator/(const mint &lhs, const mint &rhs) {
    return mint(lhs) /= rhs;
  }
  friend bool operator==(const mint &lhs, const mint &rhs) {
    return lhs._v == rhs._v;
  }
  friend bool operator!=(const mint &lhs, const mint &rhs) {
    return lhs._v != rhs._v;
  }

 private:
  unsigned int _v;
  static constexpr unsigned int umod() { return m; }
  static constexpr bool prime = internal::is_prime<m>;
};

template <int id>
struct dynamic_modint : internal::modint_base {
  using mint = dynamic_modint;

 public:
  static int mod() { return (int) (bt.umod()); }
  static void set_mod(int m) {
    assert(1 <= m);
    bt = internal::barrett(m);
  }
  static mint raw(int v) {
    mint x;
    x._v = v;
    return x;
  }

  dynamic_modint() : _v(0) {}
  template <class T, internal::is_signed_int_t<T> * = nullptr>
  dynamic_modint(T v) {
    long long x = (long long) (v % (long long) (mod()));
    if (x < 0) x += mod();
    _v = (unsigned int) (x);
  }
  template <class T, internal::is_unsigned_int_t<T> * = nullptr>
  dynamic_modint(T v) {
    _v = (unsigned int) (v % mod());
  }

  unsigned int val() const { return _v; }

  mint &operator++() {
    _v++;
    if (_v == umod()) _v = 0;
    return *this;
  }
  mint &operator--() {
    if (_v == 0) _v = umod();
    _v--;
    return *this;
  }
  mint operator++(int) {
    mint result = *this;
    ++*this;
    return result;
  }
  mint operator--(int) {
    mint result = *this;
    --*this;
    return result;
  }

  mint &operator+=(const mint &rhs) {
    _v += rhs._v;
    if (_v >= umod()) _v -= umod();
    return *this;
  }
  mint &operator-=(const mint &rhs) {
    _v += mod() - rhs._v;
    if (_v >= umod()) _v -= umod();
    return *this;
  }
  mint &operator*=(const mint &rhs) {
    _v = bt.mul(_v, rhs._v);
    return *this;
  }
  mint &operator/=(const mint &rhs) { return *this = *this * rhs.inv(); }

  mint operator+() const { return *this; }
  mint operator-() const { return mint() - *this; }

  mint pow(long long n) const {
    assert(0 <= n);
    mint x = *this, r = 1;
    while (n) {
      if (n & 1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  mint inv() const {
    auto eg = internal::inv_gcd(_v, mod());
    assert(eg.first == 1);
    return eg.second;
  }

  friend mint operator+(const mint &lhs, const mint &rhs) {
    return mint(lhs) += rhs;
  }
  friend mint operator-(const mint &lhs, const mint &rhs) {
    return mint(lhs) -= rhs;
  }
  friend mint operator*(const mint &lhs, const mint &rhs) {
    return mint(lhs) *= rhs;
  }
  friend mint operator/(const mint &lhs, const mint &rhs) {
    return mint(lhs) /= rhs;
  }
  friend bool operator==(const mint &lhs, const mint &rhs) {
    return lhs._v == rhs._v;
  }
  friend bool operator!=(const mint &lhs, const mint &rhs) {
    return lhs._v != rhs._v;
  }

 private:
  unsigned int _v;
  static internal::barrett bt;
  static unsigned int umod() { return bt.umod(); }
};
template <int id>
internal::barrett dynamic_modint<id>::bt(998244353);

using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;
using modint = dynamic_modint<-1>;

namespace internal {

template <class T>
using is_static_modint = std::is_base_of<internal::static_modint_base, T>;

template <class T>
using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;

template <class>
struct is_dynamic_modint : public std::false_type {};
template <int id>
struct is_dynamic_modint<dynamic_modint<id>> : public std::true_type {};

template <class T>
using is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;

}  // namespace internal

}  // namespace atcoder

#endif  // ATCODER_MODINT_HPP

// #include "atcoder/modint.hpp"

#ifndef ETHANKIM8683_TYPE_TRAITS
#define ETHANKIM8683_TYPE_TRAITS 1

#include <type_traits>
#include <vector>

// #include "atcoder/modint"

template <typename T>
struct type_container {
  using type = T;
};

// https://stackoverflow.com/a/38853594/19662543
template <typename T>
struct double_width;
template <>
struct double_width<char> : type_container<short> {};
template <>
struct double_width<short> : type_container<int> {};
template <>
struct double_width<int> : type_container<long long> {};
template <>
struct double_width<long> : type_container<long long> {};
template <>
struct double_width<long long> : type_container<__int128> {};
template <>
struct double_width<unsigned char> : type_container<unsigned short> {};
template <>
struct double_width<unsigned short> : type_container<unsigned int> {};
template <>
struct double_width<unsigned int> : type_container<unsigned long long> {};
template <>
struct double_width<unsigned long> : type_container<unsigned long long> {};
template <>
struct double_width<unsigned long long> : type_container<unsigned __int128> {};
template <>
struct double_width<float> : type_container<double> {};
template <>
struct double_width<double> : type_container<long double> {};
template <int MOD>
struct double_width<atcoder::static_modint<MOD>>
    : type_container<atcoder::static_modint<MOD>> {};
template <int ID>
struct double_width<atcoder::dynamic_modint<ID>>
    : type_container<atcoder::dynamic_modint<ID>> {};

// https://stackoverflow.com/a/16337657
template <typename>
struct is_vector : std::false_type {};
template <typename T, typename S>
struct is_vector<std::vector<T, S>> : std::true_type {};
template <typename, typename>
struct is_vector_of : std::false_type {};
template <typename T, typename S>
struct is_vector_of<T, std::vector<T, S>> : std::true_type {};

#endif  // ETHANKIM8683_TYPE_TRAITS

// #include "ethankim8683/type_traits.hpp"
#ifndef ETHANKIM8683_ALGEBRA
#define ETHANKIM8683_ALGEBRA 1

#include <assert.h>

#include <algorithm>
#include <bit>
#include <tuple>
#include <type_traits>
#include <vector>

// #include "atcoder/modint"
// #include "ethankim8683/type_traits"

// https://en.algorithmica.org/hpc/number-theory/montgomery/
// https://cp-algorithms.com/algebra/montgomery_multiplication.html
// Fast modular multiplication using Montgomery space
template <typename T,
          std::enable_if<std::is_integral<T>::value and
                         std::is_unsigned<T>::value>::type * = nullptr>
struct montgomery {
 private:
  using T2 = double_width<T>::type;
  using TS = std::make_signed<T>::type;
  static constexpr size_t TW = 8 * sizeof(T);

  T n, nr, r2;

 public:
  constexpr montgomery(T _n) : n(_n) {
    nr = 1;
    for (int i = 1; i < TW; i *= 2) {
      nr *= 2 - n * nr;
    }

    r2 = ((T2) 1 << (TW + TW / 2)) % n;
    r2 = mul(r2, r2);
  }

  // Divide by r
  T reduce(T2 x) const {
    T q = (T) x * nr;
    TS rv = (x >> TW) - ((T2) q * n >> TW);
    if (rv < 0) {
      rv += n;
    }
    return rv;
  }

  // Multiply by r
  T transform(T x) const { return mul(x, r2); }

  T mul(T x, T y) const { return reduce((T2) x * y); }
};

template <typename T>
T mod_pow(T x, T y, T m) {
  using T2 = double_width<T>::type;

  T rv = 1;
  for (x %= m; y; y >>= 1, x = (T2) x * x % m) {
    if (y & 1) {
      rv = (T2) rv * x % m;
    }
  }
  return rv;
}

// https://cp-algorithms.com/algebra/primality_tests.html
// Primality checking using Miller-Rabin primality test
// O(\ln^2 N)
template <typename T, std::enable_if<std::is_integral<T>::value and
                                     std::is_unsigned<T>::value and
                                     (sizeof(T) <= 64)>::type * = nullptr>
bool miller_rabin(T n) {
  using T2 = double_width<T>::type;
  using UT = std::make_unsigned<T>::type;

  if (n < 2) return false;

  auto check_composite = [&](T n, T a, T d, int s) -> bool {
    T x = 1;
    for (; d; d >>= 1, a = (T2) a * a % n) {
      if (d & 1) {
        x = (T2) x * a % n;
      }
    }
    if (x == 1 or x == n - 1) return false;
    for (int i = 0; i < s - 1; i++) {
      x = (T2) x * x % n;
      if (x == n - 1) return false;
    }
    return true;
  };

  T d = n - 1;
  int s = std::countr_zero((UT) d);
  d >>= s;
  for (auto a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n == a) return true;
    if (check_composite(n, a, d, s)) return false;
  }
  return true;
}

template <typename T,
          std::enable_if<std::is_integral<T>::value and
                         std::is_unsigned<T>::value>::type * = nullptr>
bool is_prime(T n) {
  return miller_rabin(n);
}

// https://en.algorithmica.org/hpc/algorithms/factorization/#lookup-table
// Constexpr factorization table
struct __prime_sieve_precalc {
  unsigned char sieve[1 << 16];

  constexpr __prime_sieve_precalc() : sieve(0) {
    for (int i = 2; i < (1 << 8); i++) {
      if (sieve[i]) continue;
      for (int j = i * i; j < (1 << 16); j += i) {
        if (!sieve[j]) {
          sieve[j] = i;
        }
      }
    }
  }
};
unsigned short prime_sieve(unsigned short n) {
  static constexpr __prime_sieve_precalc pc;
  unsigned short rv = pc.sieve[n];
  return rv ? rv : n;
}

// https://en.algorithmica.org/hpc/algorithms/factorization/#precomputed-primes
// Constexpr trial division
struct __trial_division_precalc {
  unsigned long long magic_primes[6542];

  constexpr __trial_division_precalc() {
    bool comp[1 << 16] = {false};
    for (int i = 2, t = 0; i < (1 << 16); i++) {
      if (comp[i]) continue;
      magic_primes[t++] = (unsigned long long) -1 / i + 1;
      for (int j = 2 * i; j < (1 << 16); j += i) {
        comp[j] = true;
      }
    }
  }
};
unsigned trial_division(unsigned n, int &i) {
  static constexpr __trial_division_precalc pc;
  for (; i < 6542; i++) {
    auto p = pc.magic_primes[i];
    if (p * n < p) return (unsigned long long) -1 / p + 1;
  }
  return n;
}
unsigned short trial_division(unsigned n) {
  int i;
  return trial_division(n, i);
}

// https://cp-algorithms.com/algebra/factorization.html#brents-algorithm
// https://en.algorithmica.org/hpc/algorithms/factorization/#pollard-brent-algorithm
// Finds factors using Pollard's rho algorithm (with Brent's optimization)
// O(\sqrt{N}) (O(N^{1/4}) according to Brent)
template <typename T,
          std::enable_if<std::is_integral<T>::value and
                         std::is_unsigned<T>::value>::type * = nullptr>
T pollard_rho(T n, T x = 2, T c = 1, int block_size = 1024) {
  using T2 = double_width<T>::type;

  if (n % 2 == 0) return 2;

  montgomery<T> m(n);
  x = m.transform(x);

  auto f = [&](T x) -> T { return m.mul(x, x) + c; };
  auto abs_diff = [&](T x, T y) -> T { return x < y ? y - x : x - y; };

  for (int l = 1;; l *= 2) {
    T y = x;
    for (int i = 1; i < l; i++) {
      x = f(x);
    }

    for (int i = 0; i < l; i += block_size) {
      T x0 = x, accum = 1;
      for (int j = 0; j < block_size and i + j < l; j++) {
        x = f(x);
        accum = m.mul(accum, abs_diff(x, y));
      }

      T g = std::gcd(accum, n);
      if (g != 1) {
        if (g == n) {
          x = x0;
          do {
            x = f(x);
            g = std::gcd(abs_diff(x, y), n);
          } while (g == 1);
        }
        return g;
      }
    }
  }
}

// https://en.algorithmica.org/hpc/algorithms/factorization/#further-improvements
// Factorization approach based on size of number
template <typename T,
          std::enable_if<std::is_integral<T>::value and
                         std::is_unsigned<T>::value>::type * = nullptr>
T find_factor(T n) {
  if (n < (1 << 16)) {
    return prime_sieve(n);
  } else if (n < (1ll << 32)) {
    return trial_division(n);
  } else {
    T x0 = 2, c = 1, f;
    do f = pollard_rho(n, x0, c++);
    while (f == n);
    return f;
  }
}
template <typename T,
          std::enable_if<std::is_integral<T>::value and
                         std::is_unsigned<T>::value>::type * = nullptr>
std::vector<T> factorize(T n) {
  std::vector<T> stack, primes;
  stack.push_back(n);
  while (stack.size() > 0) {
    T k = stack.back();
    stack.pop_back();

    if (k < (1 << 16)) {
      while (k > 1) {
        auto p = prime_sieve(k);
        primes.push_back(p);
        k /= p;
      }
    } else if (k < (1ll << 32)) {
      int i = 0;
      while (k > 1) {
        auto p = trial_division(k, i);
        primes.push_back(p);
        k /= p;
      }
    } else {
      if (is_prime(k)) {
        primes.push_back(k);
        continue;
      }

      T x0 = 524287, c = 2147483647, f;
      do f = pollard_rho(k, x0, c++);
      while (f == k);
      stack.push_back(f);
      stack.push_back(k / f);
    }
  }
  return primes;
}

// https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
// Finds solutions to ax + by = gcd(a, b) for non-negative a, b
template <typename T,
          std::enable_if<std::is_integral<T>::value and
                         std::is_unsigned<T>::value>::type * = nullptr>
std::tuple<T, T, T> eegcd(T a, T b) {
  T x = 1, y = 0, z = 0, w = 1;
  while (b) {
    T q = a / b;
    std::tie(x, z) = std::make_pair(z, x - q * z);
    std::tie(y, w) = std::make_pair(w, y - q * w);
    std::tie(a, b) = std::make_pair(b, a - q * b);
  }
  return {a, x, y};
}

// https://cp-algorithms.com/algebra/linear-diophantine-equation.html#algorithmic-solution
// Finds solutions to ax + by = c
template <typename T,
          std::enable_if<std::is_integral<T>::value>::type * = nullptr>
struct diop_linear_sol {
 private:
  T xi, yi, a, b;

 public:
  diop_linear_sol(T _xi, T _yi, T _a, T _b) : xi(_xi), yi(_yi), a(_a), b(_b) {}

  T x() { return xi; }
  T y() { return yi; }

  diop_linear_sol kth_succ(T k) {
    return diop_linear_sol(xi + k * b, yi - k * a, a, b);
  }

  diop_linear_sol min_nonneg_sol_for_x() {
    int k = xi / b;
    if (xi + k * b < 0) {
      k += (xi > 0) - (xi < 0);
    }
    return kth_succ(-k);
  }

  diop_linear_sol min_nonneg_sol_for_y() {
    int k = yi / b;
    if (yi - k * b < 0) {
      k += (yi < 0) - (yi > 0);
    }
    return kth_succ(k);
  }
};
template <typename T,
          std::enable_if<std::is_integral<T>::value>::type * = nullptr>
diop_linear_sol<T> diop_linear(T a, T b, T c) {
  using U = std::make_unsigned<T>::type;

  T g, x0, y0;
  std::tie(g, x0, y0) = eegcd((U) abs(a), (U) abs(b));
  assert(c % g == 0);

  x0 *= c / g;
  y0 *= c / g;
  if (a < 0) {
    x0 = -x0;
  }
  if (b < 0) {
    y0 = -y0;
  }
  return diop_linear_sol<T>(x0, y0, a, b);
}

template <typename T,
          std::enable_if<std::is_integral<T>::value and
                         std::is_unsigned<T>::value>::type * = nullptr>
T mod_inv(T n, T m) {
  auto [g, x, y] = eegcd(n, m);
  assert(g == 1);
  x %= m;
  if (x < 0) {
    x += m;
  }
  return x;
}

// https://cp-algorithms.com/algebra/primitive-root.html
// Finds a primitive root modulo n
template <typename T,
          std::enable_if<std::is_integral<T>::value and
                         std::is_unsigned<T>::value>::type * = nullptr>
bool primitive_root_exists(T n) {
  if (n == 1 or n == 2 or n == 4) return true;

  auto primes = factorize(n % 2 == 0 ? n / 2 : n);
  for (int i = 1; i < primes.size(); i++) {
    if (primes[i] != primes[0]) return false;
  }
  return true;
}
template <typename T,
          std::enable_if<std::is_integral<T>::value and
                         std::is_unsigned<T>::value>::type * = nullptr>
T find_primitive_root(T n) {
  using T2 = double_width<T>::type;

  if (n == 1) return 0;
  if (n == 2) return 1;

  auto primes = factorize(n - 1);
  std::sort(primes.begin(), primes.end());
  primes.erase(std::unique(primes.begin(), primes.end()), primes.end());
  for (T i = 2; i <= n; i++) {
    bool ok = true;
    for (auto p : primes) {
      if (mod_pow(i, (n - 1) / p, n) == 1) {
        ok = false;
        break;
      }
    }
    if (ok) return i;
  }
  return -1;
}

// https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it
// Fast Walsh-Hadamard transform
// O(N\log{N})
template <typename T, atcoder::internal::is_modint<T>::type * = nullptr>
void fwht(std::vector<T> &v) {
  assert(std::popcount(v.size()) == 1);
  int n = v.size();

  for (int k = 1; 2 * k <= n; k *= 2) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; j++) {
        T a = v[i + j], b = v[i + j + k];
        v[i + j] = a + b;
        v[i + j + k] = a - b;
      }
    }
  }
}
// TODO: Support for long long
template <typename T, atcoder::internal::is_modint<T>::type * = nullptr>
std::vector<T> xor_convolution(std::vector<T> a, std::vector<T> b) {
  assert(a.size() == b.size());
  assert(std::popcount(a.size()) == 1);
  int n = a.size();

  fwht(a);
  fwht(b);
  for (int i = 0; i < n; i++) {
    a[i] *= b[i];
  }
  fwht(a);
  T f = (T) 1 / n;
  for (auto &e : a) {
    e *= f;
  }
  return a;
}

// https://ideone.com/JNRMsQ
// Finds the maximum number of divisors of any number at most n and the number
// with the maximum number of divisors
std::pair<unsigned long long, unsigned long long> max_num_divisors(
    unsigned long long n) {
  using T2 = double_width<unsigned long long>::type;

  int primes[] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31,
                  37, 41, 43, 47, 51, 53, 59, 61, 67, 71};

  std::pair<unsigned long long, unsigned long long> rv = {0, 0};
  auto dfs = [&](auto self, int i, int jmax, unsigned long long x,
                 unsigned long long count) -> void {
    rv = max(rv, {count, x});
    if (i == std::size(primes)) return;

    for (int j = 1; j <= jmax; j++) {
      T2 x2 = (T2) x * primes[i];
      if (x2 > n) return;
      x = x2;
      self(self, i + 1, j, x, count * (j + 1));
    }
  };
  dfs(dfs, 0, 64, 1, 1);
  return rv;
}

#endif  // ETHANKIM8683_ALGEBRA

#include <bits/stdc++.h>

// #include "ethankim8683/algebra.hpp"

using namespace std;

using u64 = unsigned long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    u64 N;
    cin >> N;

    do {
      N++;
    } while (!is_prime(N));
    cout << N << '\n';
  }
}


