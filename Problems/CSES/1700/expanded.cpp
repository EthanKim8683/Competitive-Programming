// beginning of 'atcoder/internal_type_traits.hpp'
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
// end of 'atcoder/internal_type_traits.hpp'

// beginning of 'atcoder/internal_math.hpp'
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
// end of 'atcoder/internal_math.hpp'

// beginning of 'atcoder/internal_type_traits'
// #include "atcoder/internal_type_traits.hpp"
// end of 'atcoder/internal_type_traits'

// beginning of 'atcoder/internal_math'
// #include "atcoder/internal_math.hpp"
// end of 'atcoder/internal_math'

// beginning of 'atcoder/modint.hpp'
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
// end of 'atcoder/modint.hpp'

// beginning of 'ethankim8683/type_traits.hpp'
#ifndef ETHANKIM8683_TYPE_TRAITS
#define ETHANKIM8683_TYPE_TRAITS

// #include "atcoder/modint.hpp"

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

#endif  // ETHANKIM8683_TYPE_TRAITS
// end of 'ethankim8683/type_traits.hpp'

// beginning of 'ethankim8683/data_structures.hpp'
#ifndef ETHANKIM8683_DATA_STRUCTURES
#define ETHANKIM8683_DATA_STRUCTURES

#include <algorithm>
#include <bit>
#include <functional>
#include <vector>

// The top two elements of a map whose entries are ordered by value
template <typename T, typename S>
struct top_two {
 private:
  struct element {
    T val;
    S from;
  };

  T nil_val;
  S nil_from;
  std::function<T(T, T)> cmp;

 public:
  element first, second;

  top_two(T _nil_val, S _nil_from, const std::function<T(T, T)> &_cmp)
      : nil_val(_nil_val),
        nil_from(_nil_from),
        cmp(_cmp),
        first(nil_val, nil_from),
        second(nil_val, nil_from) {}

  bool put(T val, S from) {
    if (cmp(val, first.val)) {
      if (from != first.from) {
        second = first;
      }
      first.val = val;
      first.from = from;
      return true;
    }

    if (from != first.from and cmp(val, second.val)) {
      second.val = val;
      second.from = from;
      return true;
    }

    return false;
  }

  bool merge(const top_two<T, S> &that) {
    bool f = put(that.first), s = put(that.second);
    return f or s;
  }
};

template <typename T>
struct sparse_table {
 private:
  int n;
  T nil;
  std::function<T(T, T)> op;
  std::vector<std::vector<T>> table;

 public:
  sparse_table(const std::vector<T> &v, T _nil,
               const std::function<T(T, T)> &_op)
      : n(v.size()),
        nil(_nil),
        op(_op),
        table(std::bit_width((unsigned) n), std::vector<T>(n, nil)) {
    std::copy(v.begin(), v.end(), table[0].begin());
    for (int i = 1; i < table.size(); i++) {
      for (int j = 0; j + (1 << i) <= n; j++) {
        table[i][j] = op(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  T query(int l, int r) const {
    if (l >= r) return nil;

    int d = std::bit_width((unsigned) (r - l)) - 1;
    return op(table[d][l], table[d][r - (1 << d)]);
  }
};

// https://atcoder.jp/contests/abc328/editorial/7664
// DSU with edge voltages to measure node potentials
template <typename T>
struct dsu_with_potentials {
 private:
  int n;
  std::function<T(T, T)> op;
  std::function<T(T)> inv;
  std::vector<int> par;
  std::vector<T> V;

 public:
  dsu_with_potentials(int _n, T nil, const std::function<T(T, T)> &_op,
                      const std::function<T(T, T)> &_inv)
      : n(_n), op(_op), inv(_inv), par(n, -1), V(n, nil) {}

  int leader(int a) {
    if (par[a] < 0) return a;
    int p = leader(par[a]);
    V[a] = op(V[a], V[par[a]]);
    return par[a] = p;
  }

  bool merge(int a, int b, T v) {
    int a_ = leader(a), b_ = leader(b);
    if (a_ == b_) return op(V[b], inv(V[a])) == v;
    if (par[a_] > par[b_]) {
      std::swap(a_, b_);
      std::swap(a, b);
      v = inv(v);
    }
    par[a_] += par[b_];
    par[b_] = a_;
    V[b_] = op(op(v, V[a]), inv(V[b]));
    return true;
  }

  bool same(int a, int b) { return leader(a) == leader(b); }

  int size(int a) const { return -par[a]; }

  T potential(int a) {
    leader(a);
    return V[a];
  }

  T voltage(int a, int b) { return op(potential(b), inv(potential(a))); }
};

#endif  // ETHANKIM8683_DATA_STRUCTURES
// end of 'ethankim8683/data_structures.hpp'

// beginning of 'ethankim8683/trees.hpp'
#ifndef ETHANKIM8683_TREES
#define ETHANKIM8683_TREES

#include <assert.h>

#include <algorithm>
#include <bit>
#include <functional>
#include <iostream>  // REMOVE LATER!
#include <random>
#include <tuple>
#include <vector>

// #include "ethankim8683/data_structures.hpp"
// #include "ethankim8683/type_traits.hpp"

// Euler tour and binary lifting-based tree utils
struct tree_utils {
 private:
  const std::vector<std::vector<int>> &adj;
  int n, logn;
  int r;
  std::vector<int> in, out;
  std::vector<int> depth;
  std::vector<std::vector<int>> anc;

 public:
  tree_utils(const std::vector<std::vector<int>> &_adj, int _r = 0)
      : adj(_adj),
        n(adj.size()),
        logn(std::bit_width((unsigned) n)),
        r(_r),
        in(n),
        out(n),
        depth(n),
        anc(n, std::vector<int>(logn)) {
    int t = 0;
    auto dfs = [&](auto self, int a, int p, int d) -> void {
      in[a] = t++;
      anc[a][0] = p;
      depth[a] = d;
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a, d + 1);
      }
      out[a] = t;
    };
    dfs(dfs, r, r, 0);

    for (int i = 1; i < logn; i++) {
      for (int j = 0; j < n; j++) {
        anc[j][i] = anc[anc[j][i - 1]][i - 1];
      }
    }
  }

  int get_index(int a) const { return in[a]; }
  std::pair<int, int> get_range(int a) const { return {in[a], out[a]}; }

  int get_depth(int a) const { return depth[a]; }

  bool is_anc(int a, int b) const {
    return in[a] <= in[b] and out[a] >= out[b];
  }

  int lca(int a, int b) const {
    if (is_anc(a, b)) return a;
    if (is_anc(b, a)) return b;

    for (int i = logn - 1; i >= 0; i--) {
      if (!is_anc(anc[a][i], b)) {
        a = anc[a][i];
      }
    }
    return anc[a][0];
  }

  int dist(int a, int b) const {
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
  }

  int kth_anc(int a, int k) const {
    assert(0 <= k and k <= depth[a]);
    for (int i = logn - 1; i >= 0; i--) {
      if (k >> i & 1) {
        a = anc[a][i];
      }
    }
    return a;
  }

  int kth_on_path(int a, int b, int k) const {
    assert(0 <= k and k <= dist(a, b));
    int c = lca(a, b);
    if (k <= dist(a, c)) {
      return kth_anc(a, k);
    } else {
      return kth_anc(b, dist(a, b) - k);
    }
  }

  bool is_on_path(int a, int b, int c) const {
    return is_anc(lca(a, b), c) and (is_anc(c, a) or is_anc(c, b));
  }

  bool is_in_subtree(int a, int b, int r) const { return is_on_path(r, b, a); }
  bool is_in_subtree(int a, int b) const { return is_in_subtree(a, b, r); }

  // https://www.youtube.com/watch?v=czySm7bUHgY
  // Returns the edges of a virtual tree corresponding to the given vertices
  // O(V\log V)
  std::vector<std::pair<int, int>> virtual_tree(std::vector<int> v) const {
    for (auto a : v) {
      assert(0 <= a and a < n);
    }

    int k = v.size();

    auto cmp = [&](int a, int b) -> bool { return in[a] < in[b]; };
    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i + 1 < k; i++) {
      v.push_back(lca(v[i], v[i + 1]));
    }
    sort(v.begin(), v.end(), cmp);
    v.erase(unique(v.begin(), v.end()), v.end());

    std::vector<int> stack;
    std::vector<std::pair<int, int>> rv;
    for (auto a : v) {
      while (stack.size() >= 2 and !is_anc(stack.back(), a)) {
        rv.push_back({stack.end()[-2], stack.back()});
        stack.pop_back();
      }
      stack.push_back(a);
    }
    while (stack.size() >= 2) {
      rv.push_back({stack.end()[-2], stack.back()});
      stack.pop_back();
    }
    return rv;
  }

  std::vector<int> subtree(int r) {
    std::vector<int> rv;
    auto dfs = [&](auto self, int a, int p) -> void {
      rv.push_back(a);
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
      }
    };
    dfs(dfs, r, anc[r][0]);
    return rv;
  }
};

// https://codeforces.com/blog/entry/124286
// https://atcoder.jp/contests/abc351/editorial/9899
// pajenegod's re-root template, with AtCoder/Static Top Tree-inspired structure
// O(N)
template <typename T, typename S>
std::pair<std::vector<T>, std::vector<std::vector<T>>> rrdp(
    const std::vector<std::vector<int>> &adj, S nil,
    const std::function<S(T, int, int)> &transition,
    const std::function<S(S, S)> &combine,
    const std::function<T(S, int)> &finalize) {
  int n = adj.size();

  std::vector<S> draft_dp(n);
  std::vector<std::vector<T>> adj_dp(n);
  auto dfs_up = [&](auto self, int a, int p = -1) -> T {
    adj_dp[a].resize(adj[a].size());
    draft_dp[a] = nil;

    for (int i = 0; i < adj[a].size(); i++) {
      int b = adj[a][i];
      if (b == p) continue;

      adj_dp[a][i] = self(self, b, a);
      draft_dp[a] = combine(draft_dp[a], transition(adj_dp[a][i], a, i));
    }

    return finalize(draft_dp[a], a);
  };
  dfs_up(dfs_up, 0);

  std::vector<T> dp(n);
  auto dfs_down = [&](auto self, int a, int p = -1) -> void {
    std::vector<S> prefix_dp(adj[a].size(), nil);
    for (int i = 0; i + 1 < adj[a].size(); i++) {
      prefix_dp[i + 1] = combine(prefix_dp[i], transition(adj_dp[a][i], a, i));
    }

    std::vector<S> suffix_dp(adj[a].size(), nil);
    for (int i = adj[a].size() - 1; i - 1 >= 0; i--) {
      suffix_dp[i - 1] = combine(transition(adj_dp[a][i], a, i), suffix_dp[i]);
    }

    for (int i = 0; i < adj[a].size(); i++) {
      int b = adj[a][i];
      if (b == p) continue;

      int j = std::find(adj[b].begin(), adj[b].end(), a) - adj[b].begin();
      adj_dp[b][j] = finalize(combine(prefix_dp[i], suffix_dp[i]), a);
      dp[b] = finalize(combine(draft_dp[b], transition(adj_dp[b][j], b, j)), b);

      self(self, b, a);
    }
  };
  dfs_down(dfs_down, 0);
  dp[0] = finalize(draft_dp[0], 0);

  return {dp, adj_dp};
}

// Returns a rooted tree corresponding to the Cartesian tree
template <typename T>
std::pair<int, std::vector<std::vector<int>>> cartesian_tree(
    const std::vector<T> &v,
    const std::function<bool(T, T)> &cmp = std::less<T>()) {
  int n = v.size();

  std::vector<int> domain(n);
  iota(domain.begin(), domain.end(), 0);
  sparse_table<int> st(domain, -1, [&](int a, int b) -> int {
    if (a == -1) return b;
    if (b == -1) return a;
    return v[a] == v[b] ? std::min(a, b) : cmp(v[a], v[b]) ? a : b;
  });

  std::vector<std::vector<int>> adj(n);
  auto dfs = [&](auto self, int l, int r) -> int {
    auto m = st.query(l, r);
    if (l < m) {
      adj[m].push_back(self(self, l, m));
    }
    if (m + 1 < r) {
      adj[m].push_back(self(self, m + 1, r));
    }
    return m;
  };
  int r = dfs(dfs, 0, n);
  return {r, adj};
}

// Returns all (one or two) centroids of the tree
std::vector<int> find_centroids(const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  std::vector<int> size(n);
  auto dfs_size = [&](auto self, int a, int p) -> int {
    size[a] = 1;
    for (auto b : adj[a]) {
      if (b == p) continue;
      size[a] += self(self, b, a);
    }
    return size[a];
  };
  dfs_size(dfs_size, 0, -1);

  std::vector<int> rv;
  auto dfs_find = [&](auto self, int a, int p) -> void {
    for (auto b : adj[a]) {
      if (b == p) continue;
      if (size[b] * 2 > n) {
        return self(self, b, a);
      } else if (size[b] * 2 == n) {
        rv.push_back(b);
      }
    }
    rv.push_back(a);
  };
  dfs_find(dfs_find, 0, -1);
  return rv;
}

// Returns a rooted tree corresponding to the centroid decomposition
std::pair<int, std::vector<std::vector<int>>> centroid_decomp(
    const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  std::vector<bool> cut(n, false);
  std::vector<int> size(n);
  auto dfs_size = [&](auto self, int a, int p) -> int {
    size[a] = 1;
    for (auto b : adj[a]) {
      if (b == p or cut[b]) continue;
      size[a] += self(self, b, a);
    }
    return size[a];
  };

  auto dfs_find = [&](auto self, int a, int p, int k) -> int {
    for (auto b : adj[a]) {
      if (b == p or cut[b]) continue;
      if (size[b] * 2 > k) {
        return self(self, b, a, k);
      }
    }
    return a;
  };

  std::vector<std::vector<int>> adj_(n);
  auto dfs_build = [&](auto self, int a) -> int {
    a = dfs_find(dfs_find, a, -1, dfs_size(dfs_size, a, -1));
    cut[a] = true;
    for (auto b : adj[a]) {
      if (cut[b]) continue;
      adj_[a].push_back(self(self, b));
    }
    return a;
  };
  int r = dfs_build(dfs_build, 0);
  return {r, adj_};
}

// https://rng-58.blogspot.com/2017/02/hashing-and-probability-of-collision.html
// Returns a hash of the unlabeled rooted tree
template <typename T = long long, T MOD = (1ll << 61) - 1,
          std::enable_if<std::is_integral<T>::value>::type * = nullptr>
T tree_hash(const std::vector<std::vector<int>> &adj, int r) {
  using T2 = double_width<T>::type;

  int n = adj.size();

  std::vector<int> depth(n);
  auto dfs_depth = [&](auto self, int a, int p) -> void {
    depth[a] = 0;
    for (auto b : adj[a]) {
      if (b == p) continue;
      self(self, b, a);
      depth[a] = std::max(depth[a], depth[b] + 1);
    }
  };
  dfs_depth(dfs_depth, r, -1);

  static std::mt19937_64 rng(time(nullptr));
  static std::vector<T> vars = {1};
  while (vars.size() < depth[r] + 1) {
    vars.push_back(rng() % MOD);
  }

  auto dfs_hash = [&](auto self, int a, int p) -> T {
    T hash = 1;
    for (auto b : adj[a]) {
      if (b == p) continue;
      hash = (T2) hash * (vars[depth[a]] + self(self, b, a)) % MOD;
    }
    return hash;
  };
  return dfs_hash(dfs_hash, r, -1);
}

// Returns a hash of the unlabeled unrooted tree
template <typename T = long long, T MOD = (1ll << 61) - 1,
          std::enable_if<std::is_integral<T>::value>::type * = nullptr>
T tree_hash(const std::vector<std::vector<int>> &adj) {
  using T2 = double_width<T>::type;

  int n = adj.size();

  static T base = std::mt19937_64(time(nullptr))() % MOD;
  auto roots = find_centroids(adj);
  T rv = 0;
  for (auto r : roots) {
    rv = ((T2) rv * base + tree_hash<T, MOD>(adj, r)) % MOD;
  }
  return rv;
}

#endif  // ETHANKIM8683_TREES
// end of 'ethankim8683/trees.hpp'

// beginning of 'main'
#include <bits/stdc++.h>

// #include "ethankim8683/trees.hpp"

using namespace std;

using i64 = long long;

const i64 BASE = 6969;
const i64 MOD = (1ll << 61) - 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<vector<int>> adj1(N);
    for (int i = 0; i < N - 1; i++) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj1[a].push_back(b);
      adj1[b].push_back(a);
    }

    vector<vector<int>> adj2(N);
    for (int i = 0; i < N - 1; i++) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj2[a].push_back(b);
      adj2[b].push_back(a);
    }

    cout << (tree_hash(adj1, 0) == tree_hash(adj2, 0) ? "YES" : "NO") << '\n';
  }
}
// end of 'main'