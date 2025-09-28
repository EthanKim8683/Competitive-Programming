#ifndef ETHANKIM8683_INT
#define ETHANKIM8683_INT 1

#include <assert.h>

#include <iostream>
#include <type_traits>

// https://gist.github.com/mdickinson/e087001d213725a93eeb8d8f447a2f40
// Branchless integer square root without division
constexpr unsigned isqrt(unsigned long long n) {
  if (n == 0) return 0;

  const unsigned char lookup[128] = {
      0,   85,  83, 102, 71,  2,   36,  126, 15, 37,  28, 22,  87,  50,  107,
      46,  31,  10, 115, 57,  103, 98,  4,   33, 47,  58, 3,   118, 119, 109,
      116, 113, 63, 106, 108, 38,  120, 61,  27, 62,  79, 101, 35,  41,  104,
      13,  84,  17, 95,  53,  76,  121, 88,  34, 59,  97, 111, 5,   67,  54,
      72,  82,  52, 78,  127, 42,  44,  25,  56, 125, 91, 1,   112, 90,  99,
      105, 40,  77, 20,  81,  96,  117, 12,  70, 24,  29, 123, 94,  80,  69,
      124, 9,   8,  18,  11,  14,  64,  21,  19, 89,  7,  66,  100, 65,  48,
      26,  92,  86, 23,  114, 43,  110, 32,  74, 51,  6,  39,  93,  68,  30,
      16,  122, 60, 73,  55,  45,  75,  49,
  };

  unsigned m, k, x, b;
  int tz = std::countl_zero(n);
  n >>= tz;
  m = (unsigned) n;
  k = (unsigned) (n >> 2);
  x = lookup[k >> 1 & 127];
  x += (m * x * ~x - k) * (x - ~x);
  x += (m * x * ~x - k) * (x - ~x);
  b = m * x + 2 * k;
  b ^= -(b >> 31);
  return (b - ~b) << (tz >> 1);
}
// https://stackoverflow.com/a/70550680/19662543
constexpr unsigned short isqrt(unsigned n) {
  return isqrt((unsigned long long) n);
}

constexpr int countl_zero(unsigned __int128 n) {
  if (n == 0) return 0;

  int ans = 0;
  if (n >> 64) {
    return __builtin_clzll(n >> 64);
  } else {
    return 64 + __builtin_clzll(n);
  }
  return ans;
}

constexpr int bit_width(unsigned __int128 n) { return 128 - countl_zero(n); }

constexpr int __builtin_clzlll(unsigned __int128 n) { return countl_zero(n); }

// https://scicomp.stackexchange.com/a/36163
constexpr unsigned long long isqrt(unsigned __int128 n) {
  if (n == 0) return 0;

  const unsigned long long lookup[32] = {
      0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL,
      0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL,
      0x0000000000000000ULL, 0x0000000000000000ULL, 0x85ffffffffffffffULL,
      0x8cffffffffffffffULL, 0x94ffffffffffffffULL, 0x9affffffffffffffULL,
      0xa1ffffffffffffffULL, 0xa7ffffffffffffffULL, 0xadffffffffffffffULL,
      0xb3ffffffffffffffULL, 0xb9ffffffffffffffULL, 0xbeffffffffffffffULL,
      0xc4ffffffffffffffULL, 0xc9ffffffffffffffULL, 0xceffffffffffffffULL,
      0xd3ffffffffffffffULL, 0xd8ffffffffffffffULL, 0xdcffffffffffffffULL,
      0xe1ffffffffffffffULL, 0xe6ffffffffffffffULL, 0xeaffffffffffffffULL,
      0xeeffffffffffffffULL, 0xf3ffffffffffffffULL, 0xf7ffffffffffffffULL,
      0xfbffffffffffffffULL, 0xffffffffffffffffULL};

  int lz = countl_zero(n), i = n << (lz & ~1) >> 123;
  unsigned long long y = lookup[i] >> (lz >> 1), hi = n >> 64, q;

  q = 0xffffffffffffffffULL;
  if (hi < y) q = n / y;
  y = (y + q) / 2;
  if (lz < 106) {
    q = 0xffffffffffffffffULL;
    if (hi < y) q = n / y;
    y = (y + q) / 2;
    if (lz < 86) {
      q = 0xffffffffffffffffULL;
      if (hi < y) q = n / y;
      y = (y + q) / 2;
      if (lz < 42) {
        q = 0xffffffffffffffffULL;
        if (hi < y) q = n / y;
        y = (y + q) / 2;
      }
    }
  }
  if ((unsigned __int128) y * y > n) y--;
  return y;
}

template <typename T,
          std::enable_if<std::is_integral<T>::value and
                         std::is_unsigned<T>::value>::type * = nullptr>
constexpr unsigned char ilog(T n) {
  assert(n > 0);
  return bit_width(n) - 1;
}

constexpr __int128 lllabs(__int128 n) { return n < 0 ? -n : n; }

// https://stackoverflow.com/a/25115163/19662543
std::ostream &operator<<(std::ostream &out, unsigned __int128 n) {
  std::ostream::sentry s(out);
  if (s) {
    char buf[39], *ptr = std::end(buf);
    do {
      *--ptr = '0' + n % 10;
      n /= 10;
    } while (n != 0);

    int len = std::end(buf) - ptr;
    if (out.rdbuf()->sputn(ptr, len) != len) {
      out.setstate(std::ios_base::badbit);
    }
  }
  return out;
}
std::ostream &operator<<(std::ostream &out, __int128 n) {
  std::ostream::sentry s(out);
  if (s) {
    bool neg = false;
    if (n < 0) {
      n = -n;
      neg = true;
    }

    char buf[40], *ptr = std::end(buf);
    do {
      *--ptr = '0' + n % 10;
      n /= 10;
    } while (n != 0);
    if (neg) {
      *--ptr = '-';
    }

    int len = std::end(buf) - ptr;
    if (out.rdbuf()->sputn(ptr, len) != len) {
      out.setstate(std::ios_base::badbit);
    }
  }
  return out;
}

#endif  // ETHANKIM8683_INT
