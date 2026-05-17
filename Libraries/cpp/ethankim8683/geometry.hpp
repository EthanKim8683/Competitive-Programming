#ifndef ETHANKIM8683_GEOMETRY
#define ETHANKIM8683_GEOMETRY 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <type_traits>
#include <vector>

namespace ethankim8683 {

const long double PI = std::acosl(-1);

template <class T>
struct vec2 {
  T x, y;

  vec2() : x(0), y(0) {}
  vec2(T x, T y) : x(x), y(y) {}
  template <class S>
  vec2(const vec2<S> &v) : x(v.x), y(v.y) {}
  vec2(const std::pair<T, T> &v) : x(v.x), y(v.y) {}

  operator std::pair<T, T>() const { return {x, y}; }

  vec2<T> operator+(const vec2<T> &rhs) const { return {x + rhs.x, y + rhs.y}; }
  vec2<T> operator-(const vec2<T> &rhs) const { return {x - rhs.x, y - rhs.y}; }
  vec2<T> operator*(T rhs) const { return {x * rhs, y * rhs}; }
  vec2<T> operator/(T rhs) const { return {x / rhs, y / rhs}; }
  vec2<T> operator-() const { return {-x, -y}; }

  friend vec2<T> operator*(T lhs, const vec2<T> &rhs) {
    return {lhs * rhs.x, lhs * rhs.y};
  }

  vec2<T> &operator+=(const vec2<T> &rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  vec2<T> &operator-=(const vec2<T> &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }
  vec2<T> &operator*=(T rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
  }
  vec2<T> &operator/=(T rhs) {
    x /= rhs;
    y /= rhs;
    return *this;
  }

  bool operator==(const vec2<T> &rhs) const {
    return x == rhs.x and y == rhs.y;
  }
  bool operator<(const vec2<T> &rhs) const {
    return std::pair{x, y} < std::pair{rhs.x, rhs.y};
  }
  bool operator>(const vec2<T> &rhs) const {
    return std::pair{x, y} > std::pair{rhs.x, rhs.y};
  }
  bool operator<=(const vec2<T> &rhs) const {
    return std::pair{x, y} <= std::pair{rhs.x, rhs.y};
  }
  bool operator>=(const vec2<T> &rhs) const {
    return std::pair{x, y} >= std::pair{rhs.x, rhs.y};
  }
};
template <class T>
T dot(const vec2<T> &a, const vec2<T> &b) {
  return a.x * b.x + a.y * b.y;
}
template <class T>
T cross(const vec2<T> &a, const vec2<T> &b) {
  return a.x * b.y - b.x * a.y;
}
template <class T>
T length2(const vec2<T> &x) {
  return dot(x, x);
}
template <class T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
T length(const vec2<T> &x) {
  return std::sqrt(length2(x));
}
template <class T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
T distance(const vec2<T> &a, const vec2<T> &b) {
  return length(b - a);
}
// Component of a along b
template <class T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
T comp(const vec2<T> &a, const vec2<T> &b) {
  return dot(a, b) / length(b);
}
// Projection of a onto b
template <class T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
vec2<T> proj(const vec2<T> &a, const vec2<T> &b) {
  return b * dot(a, b) / dot(b, b);
}
// Rotate 90 degrees counter-clockwise
template <class T>
vec2<T> perp(const vec2<T> &v) {
  return {-v.y, v.x};
}
template <class T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
vec2<T> rotate(const vec2<T> &v, long double theta) {
  return {v.x * std::cos(theta) - v.y * std::sin(theta),
          v.y * std::cos(theta) + v.x * std::sin(theta)};
}
template <class T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
vec2<T> normalize(const vec2<T> &x) {
  return x / length(x);
}
// https://usaco.guide/plat/sweep-line#solution---seeing-the-boundary
// Sorts vectors by angle from positive x-axis
template <class T>
struct less_radial {
  bool operator()(const vec2<T> &a, const vec2<T> &b) const {
    auto sign = [&](int x) -> int {
      if (x > 0) return 1;
      if (x < 0) return -1;
      return 0;
    };
    auto half = [&](const vec2<T> &v) -> int {
      if (sign(v.y) != 0) return sign(v.y);
      if (sign(v.x) != 0) return sign(v.x);
      assert(false);
    };
    if (half(a) != half(b)) return half(a) < half(b);
    return cross(a, b) > 0;
  }
};
template <class T>
std::istream &operator>>(std::istream &in, vec2<T> &v) {
  in >> v.x >> v.y;
  return in;
}
template <class T>
std::ostream &operator<<(std::ostream &out, const vec2<T> &v) {
  out << '(' << v.x << ", " << v.y << ')';
  return out;
}

// https://usaco.guide/plat/convex-hull?lang=cpp#with-monotone-chain
// Constructs a convex hull and returns the hull's indices in counter-clockwise
// order
// O(N\log(N))
template <class T>
std::vector<int> convex_hull(const std::vector<vec2<T>> &points) {
  std::vector<int> order(points.size());
  std::iota(order.begin(), order.end(), 0);
  std::sort(order.begin(), order.end(),
            [&](int a, int b) -> bool { return points[a] < points[b]; });

  auto area = [&](const vec2<T> &a, const vec2<T> &b, const vec2<T> &c) -> T {
    return cross(b - a, c - a);
  };

  std::vector<int> upper, lower;
  for (auto e : order) {
    while (upper.size() > 1 and area(points[upper.end()[-2]],
                                     points[upper.end()[-1]], points[e]) >= 0) {
      upper.pop_back();
    }
    upper.push_back(e);

    while (lower.size() > 1 and area(points[lower.end()[-2]],
                                     points[lower.end()[-1]], points[e]) <= 0) {
      lower.pop_back();
    }
    lower.push_back(e);
  }
  if (lower.size() <= 1) return lower;
  if (points[lower[0]] == points[lower[1]]) return {0};

  std::vector<int> rv;
  rv.insert(rv.end(), lower.begin(), lower.end());
  rv.insert(rv.end(), next(upper.rbegin()), prev(upper.rend()));
  return rv;
}

// Finds the area of the intersection between a half-plane and a circle
template <class T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
T halfplane_circle_ixn_area(const vec2<T> &r0, const vec2<T> &v,
                            const vec2<T> &c, T r) {
  T w = std::clamp(comp(c - r0, perp(v)), -r, r);
  //   \int_{-r}^w 2\sqrt{r^2-x^2} \,dx
  // = w\sqrt{r^2-w^2} + r^2\arcsin(\frac{w}{r}) + \frac{\pi r^2}{2}
  return w * std::sqrt(r * r - w * w) + r * r * std::asin(w / r) +
         PI * r * r / 2;
}

}  // namespace ethankim8683

#endif  // ETHANKIM8683_GEOMETRY
