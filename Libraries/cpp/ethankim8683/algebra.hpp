#ifndef ETHANKIM8683_ALGEBRA
#define ETHANKIM8683_ALGEBRA 1

#include <assert.h>

#include <algorithm>
#include <bit>
#include <tuple>
#include <type_traits>
#include <vector>

#include "atcoder/modint"
#include "ethankim8683/type_traits"

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
