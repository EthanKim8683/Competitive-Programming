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
#ifndef ETHANKIM8683_DATA_STRUCTURES
#define ETHANKIM8683_DATA_STRUCTURES 1

#include <assert.h>
#include <time.h>

#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
#include <random>
#include <tuple>
#include <vector>

// #include "ethankim8683/type_traits"

template <class S, auto op, auto e>
struct sparse_table {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                "op must work as S(S, S)");
  static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                "e must work as S()");

 private:
  int n;
  std::vector<std::vector<S>> table;

 public:
  sparse_table() {}
  sparse_table(const std::vector<S> &v)
      : n(v.size()), table(std::__lg(n) + 1, std::vector<S>(n, e())) {
    std::copy(v.begin(), v.end(), table[0].begin());
    for (int i = 1; i < table.size(); i++) {
      for (int j = 0; j + (1 << i) <= n; j++) {
        table[i][j] = op(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  S prod(int l, int r) const {
    if (l >= r) return e();
    int d = std::__lg(r - l);
    return op(table[d][l], table[d][r - (1 << d)]);
  }
};

// https://atcoder.jp/contests/abc328/editorial/7664
// DSU with edge voltages to measure node potentials
template <class S, auto op, auto inv>
struct dsu_with_potentials {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                "op must work as S(S, S)");
  static_assert(std::is_convertible_v<decltype(inv), std::function<S(S)>>,
                "inv must work as S(S)");

 private:
  std::vector<int> root;
  std::vector<S> V;

 public:
  dsu_with_potentials() {}
  dsu_with_potentials(int n, S nil) : root(n, -1), V(n, nil) {}

  int leader(int a) {
    if (root[a] < 0) return a;
    int p = leader(root[a]);
    V[a] = op(V[a], V[root[a]]);
    return root[a] = p;
  }

  bool merge(int a, int b, S v) {
    int a2 = leader(a), b2 = leader(b);
    if (a2 == b2) return op(V[b], inv(V[a])) == v;
    if (root[a2] > root[b2]) {
      std::swap(a2, b2);
      std::swap(a, b);
      v = inv(v);
    }
    root[a2] += root[b2];
    root[b2] = a2;
    V[b2] = op(op(v, V[a]), inv(V[b]));
    return true;
  }

  bool same(int a, int b) { return leader(a) == leader(b); }

  int size(int a) { return -root[leader(a)]; }

  S potential(int a) {
    leader(a);
    return V[a];
  }

  S voltage(int a, int b) { return op(potential(b), inv(potential(a))); }
};

// https://usaco.guide/plat/RURQ#implementation
// Fenwick tree with range updates
template <typename T>
struct range_add_fenwick_tree {
 private:
  using T2 = double_width<T>::type;

  int n;
  std::vector<T> m;
  std::vector<T2> b;

 public:
  range_add_fenwick_tree() {}
  range_add_fenwick_tree(int _n) : n(_n), m(n + 1, 0), b(n + 1, 0) {}

  void add(int l, int r, T v) {
    assert(0 <= l and l <= r and r <= n);
    for (int i = l + 1; i <= n; i += i & -i) {
      m[i] += v;
      b[i] += (T2) v * l;
    }
    for (int i = r + 1; i <= n; i += i & -i) {
      m[i] -= v;
      b[i] -= (T2) v * r;
    }
  }

  T sum(int l, int r) {
    assert(0 <= l and l <= r and r <= n);
    T2 rv = 0;
    for (int i = l; i > 0; i -= i & -i) {
      rv -= (T2) m[i] * l - b[i];
    }
    for (int i = r; i > 0; i -= i & -i) {
      rv += (T2) m[i] * r - b[i];
    }
    return rv;
  }
};

// https://usaco.guide/adv/persistent#path-copying
// Persistent array with insertion and deletion
template <typename T>
struct persistent_vector {
 private:
  struct node {
    T v;
    node *l, *r;

    node() : v(), l(nullptr), r(nullptr) {}
    node(T _v) : v(_v), l(nullptr), r(nullptr) {}
    node(T _v, node *_l, node *_r) : v(_v), l(_l), r(_r) {}
  };

  int n;
  node *root;

  persistent_vector(int _n, node *_root) : n(_n), root(_root) {}

  static int middle(int l, int r) {
    return l + (1 << std::__lg(r - l + 1)) - 1;
  }

 public:
  persistent_vector() : n(0), root(nullptr) {}

  persistent_vector(const std::vector<T> &v) : n(v.size()) {
    auto dfs = [&](auto self, int l, int r) -> node * {
      if (l > r) return nullptr;

      int m = middle(l, r);
      return new node(v[m], self(self, l, m - 1), self(self, m + 1, r));
    };
    root = dfs(dfs, 0, n - 1);
  }
  persistent_vector(int _n, T nil = T())
      : persistent_vector(std::vector<T>(_n, nil)) {}

  int size() const { return n; }
  bool empty() const { return n == 0; }

  persistent_vector<T> set(int i, T v) {
    auto dfs = [&](auto self, node *a, int l, int r) -> node * {
      int m = middle(l, r);
      if (m == i) return new node(v, a->l, a->r);

      if (i < m) {
        return new node(a->v, self(self, a->l, l, m - 1), a->r);
      } else {
        return new node(a->v, a->l, self(self, a->r, m + 1, r));
      }
    };
    return {n, dfs(dfs, root, 0, n - 1)};
  }

  T get(int i) const {
    node *a = root;
    int l = 0, r = n - 1;
    while (true) {
      int m = middle(l, r);
      if (m == i) return a->v;

      if (i < m) {
        a = a->l;
        r = m - 1;
      } else {
        a = a->r;
        l = m + 1;
      }
    }
  }

  // O(\log{N})
  persistent_vector<T> push_back(T v) {
    auto dfs = [&](auto self, node *a, int l, int r) -> node * {
      if (l > r) return new node(v);

      int m = middle(l, r);
      if (m - l == r - m) return new node(v, a, nullptr);

      return new node(a->v, a->l, self(self, a->r, m + 1, r));
    };
    return {n + 1, dfs(dfs, root, 0, n - 1)};
  }

  // O(\log{N})
  persistent_vector<T> pop_back() {
    auto dfs = [&](auto self, node *a, int l, int r) -> node * {
      int m = middle(l, r);
      if (m == r) return a->l;

      return new node(a->v, a->l, self(self, a->r, m + 1, r));
    };
    return {n - 1, dfs(dfs, root, 0, n - 1)};
  }

  // O(\log{N+K})
  persistent_vector<T> insert(int i, T v) {
    auto dfs = [&](auto self, node *a, int l, int r, bool check) -> node * {
      if (check) {
        if (l > r) return new node(v);
      } else {
        if (l > r) return nullptr;
        if (r < i) return a;
      }

      int m = middle(l, r);
      bool push = false;
      if (check) {
        push = m - l == r - m;
        check = push == false;
      }

      node *a2 = new node(a->v);
      a2->l = self(self, a->l, l, m - 1, false);
      if (m >= i) {
        a2->v = v;
        v = a->v;
      }
      a2->r = self(self, a->r, m + 1, r, check);

      if (push) {
        return new node(v, a2, nullptr);
      } else {
        return a2;
      }
    };
    return {n + 1, dfs(dfs, root, 0, n - 1, true)};
  }

  // O(\log{N+K})
  persistent_vector<T> erase(int i) {
    T v;
    auto dfs = [&](auto self, node *a, int l, int r) -> node * {
      if (l > r) return nullptr;
      if (r < i) return a;

      int m = middle(l, r);
      if (m == n - 1) {
        v = a->v;
        return self(self, a->l, l, m - 1);
      }

      node *a2 = new node(a->v);
      a2->r = self(self, a->r, m + 1, r);
      if (m >= i) {
        a2->v = v;
        v = a->v;
      }
      a2->l = self(self, a->l, l, m - 1);
      return a2;
    };
    return {n - 1, dfs(dfs, root, 0, n - 1)};
  }
};

// https://usaco.guide/adv/persistent#persistent-segment-tree
// https://github.com/atcoder/ac-library/blob/master/atcoder/segtree.hpp
template <class S, auto op, auto e>
struct persistent_segtree {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                "op must work as S(S, S)");
  static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                "e must work as S()");

 private:
  struct node {
    S v;
    node *l, *r;

    node(S _v) : v(_v), l(nullptr), r(nullptr) {}
    node(node *_l, node *_r) : v(e()), l(_l), r(_r) {
      if (l != nullptr) {
        v = op(v, l->v);
      }
      if (r != nullptr) {
        v = op(v, r->v);
      }
    }
  };

  int n;
  node *root;

  persistent_segtree(int _n, node *_root) : n(_n), root(_root) {}

 public:
  persistent_segtree() {}
  persistent_segtree(const std::vector<S> &v) : n(v.size()) {
    auto dfs = [&](auto self, int l, int r) -> node * {
      if (r - l == 1) return new node(v[l]);

      int m = l + (r - l) / 2;
      return new node(self(self, l, m), self(self, m, r));
    };
    root = dfs(dfs, 0, n);
  }
  persistent_segtree(int _n) : persistent_segtree(std::vector<S>(_n, e())) {}

  persistent_segtree<S, op, e> set(int i, S v) {
    auto dfs = [&](auto self, node *a, int l, int r) -> node * {
      if (r - l == 1) return new node(v);

      int m = l + (r - l) / 2;
      if (i < m) {
        return new node(self(self, a->l, l, m), a->r);
      } else {
        return new node(a->l, self(self, a->r, m, r));
      }
    };
    return {n, dfs(dfs, root, 0, n)};
  }

  S get(int i) const {
    node *a = root;
    int l = 0, r = n;
    while (r - l > 1) {
      int m = l + (r - l) / 2;
      if (i < m) {
        a = a->l;
        r = m;
      } else {
        a = a->r;
        l = m;
      }
    }
    return a->v;
  }

  S prod(int l, int r) const {
    auto dfs = [&](auto self, node *a, int l2, int r2) -> S {
      if (r <= l2 or r2 <= l) return e();
      if (l <= l2 and r2 <= r) return a->v;

      int m = l2 + (r2 - l2) / 2;
      return op(self(self, a->l, l2, m), self(self, a->r, m, r2));
    };
    return dfs(dfs, root, 0, n);
  }

  S all_prod() const { return root->v; }

  template <bool (*f)(S)>
  int max_right(int l) const {
    return max_right(l, [](S x) { return f(x); });
  }

  template <class F>
  int max_right(int l, F f) const {
    S v = e();
    auto dfs = [&](auto self, node *a, int l2, int r2) -> int {
      if (r2 <= l) return r2;
      if (l <= l2 and f(op(v, a->v))) {
        v = op(v, a->v);
        return r2;
      }
      if (r2 - l2 == 1) return l2;

      int m = l2 + (r2 - l2) / 2, r = self(self, a->l, l2, m);
      if (r != m) return r;
      return self(self, a->r, m, r2);
    };
    return dfs(dfs, root, 0, n);
  }

  template <bool (*f)(S)>
  int min_left(int r) const {
    return min_left(r, [](S x) { return f(x); });
  }

  template <class F>
  int min_left(int r, F f) const {
    S v = e();
    auto dfs = [&](auto self, node *a, int l2, int r2) -> int {
      if (r <= l2) return l2;
      if (r2 <= r and f(op(a->v, v))) {
        v = op(a->v, v);
        return l2;
      }
      if (r2 - l2 == 1) return r2;

      int m = l2 + (r2 - l2) / 2, l = self(self, a->r, m, r2);
      if (l != m) return l;
      return self(self, a->l, l2, m);
    };
    return dfs(dfs, root, 0, n);
  }
};

// https://usaco.guide/adv/offline-del#dsu-with-rollback
struct dsu_with_rollbacks {
 private:
  std::vector<int> root, saves;
  std::vector<std::tuple<int, int, int>> history;

 public:
  dsu_with_rollbacks() {}
  dsu_with_rollbacks(int n) : root(n, -1), saves({0}) {}

  // https://codeforces.com/blog/entry/90340?#comment-787571
  // O(\log{N})
  int leader(int a) {
    if (root[a] < 0) return a;
    return leader(root[a]);
  }

  int merge(int a, int b) {
    if ((a = leader(a)) == (b = leader(b))) return a;
    if (root[a] > root[b]) {
      std::swap(a, b);
    }
    history.push_back({a, b, root[b]});
    root[a] += root[b];
    root[b] = a;
    return a;
  }

  bool same(int a, int b) { return leader(a) == leader(b); }

  int size(int a) { return -root[leader(a)]; }

  void save() { saves.push_back(history.size()); }

  void rollback() {
    while (history.size() > saves.back()) {
      auto [a, b, size] = history.back();
      history.pop_back();
      root[a] -= size;
      root[b] = size;
    }
    saves.pop_back();
  }
};

// https://jilljenn.github.io/tryalgo/_modules/tryalgo/union_rectangles.html#union_rectangles
template <typename S, typename T>
struct cover_query {
 private:
  struct seg {
    T c;
    S s, w;
  };

  int n;
  std::vector<seg> data;

 public:
  cover_query() {}
  cover_query(const std::vector<S> &l)
      : n(1 << std::__lg(2 * l.size() - 1)), data(2 * n, {0, 0, 0}) {
    for (int i = 0; i < l.size(); i++) {
      data[n + i].w = l[i];
    }
    for (int i = n - 1; i > 0; i--) {
      data[i].w = data[i << 1].w + data[i << 1 | 1].w;
    }
  }
  cover_query(int _n) : cover_query(std::vector<S>(_n, 1)) {}

  S cover() { return data[1].s; }

  void add(int l, int r, T dc) {
    auto dfs = [&](auto self, int i, int sl, int sr) -> void {
      if (sr <= l or r <= sl) return;
      if (l <= sl and sr <= r) {
        data[i].c += dc;
      } else {
        int sm = sl + (sr - sl) / 2;
        self(self, i << 1, sl, sm);
        self(self, i << 1 | 1, sm, sr);
      }
      if (data[i].c == 0) {
        if (i >= n) {
          data[i].s = 0;
        } else {
          data[i].s = data[i << 1].s + data[i << 1 | 1].s;
        }
      } else {
        data[i].s = data[i].w;
      }
    };
    dfs(dfs, 1, 0, n);
  }
};

// https://cp-algorithms.com/data_structures/treap.html#implicit-treaps
// https://github.com/ShahjalalShohag/code-library/blob/main/Data%20Structures/Implicit%20Treap.cpp
// TODO: Generalize to support custom operations
template <typename T>
struct implicit_treap {
 private:
  static std::mt19937 rng;

  struct node {
    T v;
    node *l, *r;
    int y, size;

    node(T _v, int _y) : v(_v), l(nullptr), r(nullptr), y(_y), size(0) {}
    node(T _v) : node(_v, rng()) {}
  };

  node *root;

  static int safe_size(node *a) { return a == nullptr ? 0 : a->size; }

  static node *safe_copy(node *a) {
    if (a == nullptr) return nullptr;
    node *a2 = new node(*a);
    a2->l = safe_copy(a->l);
    a2->r = safe_copy(a->r);
    return a2;
  }

  static void safe_free(node *a) {
    if (a == nullptr) return;
    safe_free(a->l);
    safe_free(a->r);
    free(a);
  }

  static void safe_pull(node *a) {
    if (a == nullptr) return;
    a->size = safe_size(a->l) + 1 + safe_size(a->r);
  }

  static node *merge(node *l, node *r) {
    auto dfs = [&](auto self, node *&a, node *l, node *r) -> void {
      if (l == nullptr) {
        a = r;
      } else if (r == nullptr) {
        a = l;
      } else if (l->y >= r->y) {
        self(self, l->r, l->r, r);
        a = l;
      } else {
        self(self, r->l, l, r->l);
        a = r;
      }
      safe_pull(a);
    };
    node *rv;
    dfs(dfs, rv, l, r);
    return rv;
  }

  static std::pair<node *, node *> split(node *a, int i) {
    auto dfs = [&](auto self, node *a, node *&l, node *&r, int i) -> void {
      if (a == nullptr) {
        l = r = nullptr;
        return;
      }
      if (i <= safe_size(a->l)) {
        self(self, a->l, l, a->l, i);
        r = a;
      } else {
        self(self, a->r, a->r, r, i - (1 + safe_size(a->l)));
        l = a;
      }
      safe_pull(a);
    };
    node *l, *r;
    dfs(dfs, a, l, r, i);
    return {l, r};
  }

  implicit_treap(node *_root) : root(_root) {}

  node *get_node(int i) {
    assert(0 <= i and i < size());
    auto dfs = [&](auto self, node *a, int i) -> node * {
      if (i == safe_size(a->l)) {
        return a;
      } else if (i < safe_size(a->l)) {
        return self(self, a->l, i);
      } else {
        return self(self, a->r, i - (1 + safe_size(a->l)));
      }
    };
    return dfs(dfs, root, i);
  };

 public:
  implicit_treap() : root(nullptr) {}

  implicit_treap(const std::vector<int> &v) {
    auto dfs_heapify = [&](auto self, node *a) -> void {
      if (a == nullptr) return;
      node *b = a;
      if (a->l != nullptr and a->l->y > b->y) {
        b = a->l;
      }
      if (a->r != nullptr and a->r->y > b->y) {
        b = a->r;
      }
      if (b != a) {
        std::swap(a->y, b->y);
        self(self, b);
      }
    };

    auto dfs_build = [&](auto self, int l, int r) -> node * {
      if (l == r) return nullptr;
      int m = l + (r - l) / 2;
      node *a = new node(v[m]);
      a->l = self(self, l, m);
      a->r = self(self, m + 1, r);
      dfs_heapify(dfs_heapify, a);
      safe_pull(a);
      return a;
    };
    root = dfs_build(dfs_build, 0, v.size());
  }

  implicit_treap(int n, T v) : implicit_treap(std::vector<T>(n, v)) {}

  ~implicit_treap() { safe_free(root); }

  int size() const { return safe_size(root); }

  void insert(int i, T v) {
    assert(0 <= i and i <= size());
    auto [l, r] = split(root, i);
    root = merge(merge(l, new node(v)), r);
  }

  void erase(int i) {
    assert(0 <= i and i < size());
    auto [l1, r1] = split(root, i);
    auto [l2, r2] = split(r1, 1);
    safe_free(l2);
    root = merge(l1, r2);
  }

  void set(int i, T v) { get_node(i)->v = v; }

  T get(int i) { return get_node(i)->v; }
};
template <typename T>
std::mt19937 implicit_treap<T>::rng(time(nullptr));

template <typename T>
struct xor_basis {
 private:
  int n, m;
  std::vector<T> basis;

 public:
  xor_basis(int _n) : n(_n), m(0), basis(n, 0) {}
  xor_basis() : xor_basis(8 * sizeof(T)) {}

  bool insert(T x) {
    for (int i = n - 1; i >= 0; i--) {
      if (~x >> i & 1) continue;
      if (basis[i] == 0) {
        for (int j = 0; j < i; j++) {
          if (~x >> j & 1) continue;
          x ^= basis[j];
        }
        basis[i] = x;
        m++;
        for (int j = i + 1; j < n; j++) {
          if (~basis[j] >> i & 1) continue;
          basis[j] ^= x;
        }
        return true;
      }
      x ^= basis[i];
    }
    return false;
  }

  T size() { return m; }

  bool contains(T x) {
    for (int i = 0; i < n; i++) {
      if (~x >> i & 1) continue;
      if (basis[i] == 0) return false;
      x ^= basis[i];
    }
    return true;
  }

  T order_of_key(T x) {
    int x2 = 0, j = m - 1, rv = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (basis[i] == 0) continue;
      if ((x2 ^ basis[i]) <= x) {
        rv += 1 << j;
        x2 ^= basis[i];
      }
      j--;
    }
    return rv;
  }

  T find_by_order(T k) {
    int k2 = 0, j = m - 1, rv = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (basis[i] == 0) continue;
      if (k2 + (1 << j) <= k) {
        rv ^= basis[i];
        k2 += 1 << j;
      }
      j--;
    }
    return rv;
  }
};

// https://eolymp.com/en/posts/7u074ngkv127l3fl0m33bf5gck
// TODO: XOR basis with deletions

// https://codeforces.com/blog/entry/11080
template <typename T, typename Compare = std::less<T>>
using ordered_set =
    __gnu_pbds::tree<T, __gnu_pbds::null_type, Compare, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;
template <typename T, typename S, typename Compare = std::less<T>>
using ordered_map =
    __gnu_pbds::tree<T, S, Compare, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

#endif  // ETHANKIM8683_DATA_STRUCTURES

// #include "ethankim8683/data_structures.hpp"
#ifndef ETHANKIM8683_TREE
#define ETHANKIM8683_TREE 1

#include <assert.h>

#include <algorithm>
#include <functional>
#include <random>
#include <vector>

// #include "ethankim8683/data_structures"
// #include "ethankim8683/type_traits"

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
        logn(std::__lg(n) + 1),
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
  // O(V\log{V})
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
// O(N)
template <typename T>
std::pair<int, std::vector<std::vector<int>>> cartesian_tree(
    const std::vector<T> &v,
    const std::function<bool(T, T)> &cmp = std::less<T>()) {
  int n = v.size();

  std::vector<int> domain(n);
  iota(domain.begin(), domain.end(), 0);

  using S = int;
  auto op = [&](S a, S b) -> S {
    if (a == -1) return b;
    if (b == -1) return a;
    return v[a] == v[b] ? std::min(a, b) : cmp(v[a], v[b]) ? a : b;
  };
  auto e = [&]() -> int { return -1; };
  sparse_table<S, op, e> st(domain);

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
// O(N)
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
// O(N\log{N})
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

  std::vector<std::vector<int>> adj2(n);
  auto dfs_build = [&](auto self, int a) -> int {
    a = dfs_find(dfs_find, a, -1, dfs_size(dfs_size, a, -1));
    cut[a] = true;
    for (auto b : adj[a]) {
      if (cut[b]) continue;
      adj2[a].push_back(self(self, b));
    }
    return a;
  };
  int r = dfs_build(dfs_build, 0);
  return {r, adj2};
}

// https://rng-58.blogspot.com/2017/02/hashing-and-probability-of-collision.html
// Returns a hash of the unlabeled rooted tree
// O(N)
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
// O(N)
template <typename T = long long, T MOD = (1ll << 61) - 1,
          std::enable_if<std::is_integral<T>::value>::type * = nullptr>
T tree_hash(const std::vector<std::vector<int>> &adj) {
  using T2 = double_width<T>::type;

  int n = adj.size();

  auto roots = find_centroids(adj);
  std::vector<T> hashes;
  for (auto r : roots) {
    hashes.push_back(tree_hash<T, MOD>(adj, r));
  }
  sort(hashes.begin(), hashes.end());

  static T base = std::mt19937_64(time(nullptr))() % MOD;
  T rv = 0;
  for (auto e : hashes) {
    rv = ((T2) rv * base + e) % MOD;
  }
  return rv;
}

#endif  // ETHANKIM8683_TREE

#include <bits/stdc++.h>

// #include "ethankim8683/tree.hpp"

using namespace std;

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

    cout << (tree_hash(adj1) == tree_hash(adj2) ? "YES" : "NO") << '\n';
  }
}


