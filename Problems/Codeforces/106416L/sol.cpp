#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vc<int> vi;

struct fraction {
  int p, q;
  fraction(int p, int q) : p(p), q(q) { normalize(); }
  fraction(int x) : p(x), q(1) {}
  void normalize() {
    int g = gcd(p, q);
    p /= g;
    q /= g;
    if (q < 0) {
      p = -p;
      q = -q;
    }
  }
  fraction operator-() const { return {-p, q}; }
  fraction &operator+=(const fraction &rhs) {
    p = p * rhs.q + rhs.p * q;
    q = q * rhs.q;
    normalize();
    return *this;
  }
  fraction &operator-=(const fraction &rhs) {
    *this += -rhs;
    return *this;
  }
  fraction &operator*=(const fraction &rhs) {
    p *= rhs.p;
    q *= rhs.q;
    normalize();
    return *this;
  }
  fraction &operator/=(const fraction &rhs) {
    p *= rhs.q;
    q *= rhs.p;
    normalize();
    return *this;
  }
  fraction operator+(const fraction &rhs) const {
    return fraction(*this) += rhs;
  }
  fraction operator-(const fraction &rhs) const {
    return fraction(*this) -= rhs;
  }
  fraction operator*(const fraction &rhs) const {
    return fraction(*this) *= rhs;
  }
  fraction operator/(const fraction &rhs) const {
    return fraction(*this) /= rhs;
  }
  bool operator<(const fraction &rhs) const { return p * rhs.q < rhs.p * q; };
  bool operator==(const fraction &rhs) const { return p * rhs.q == rhs.p * q; };
  friend fraction abs(const fraction &x) { return {abs(x.p), x.q}; }
  friend ostream &operator<<(ostream &out, fraction x) {
    out << x.p << '/' << x.q;
    return out;
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, C, L;
  cin >> N >> C >> L;

  vc<pii> pedestrian(N);
  for (auto &[x, v] : pedestrian) {
    cin >> x >> v;
  }
  pedestrian.eb(0, 0);
  pedestrian.eb(L, 0);
  N += 2;

  int Q;
  cin >> Q;

  vi T(Q);
  for (auto &e : T) cin >> e;

  vc<tuple<fraction, int, int, int, int, int>> events;

  vc is_far(N, vc<bool>(N));
  rep(i, 0, N) {
    rep(j, i + 1, N) {
      auto [x1, v1] = pedestrian[i];
      auto [x2, v2] = pedestrian[j];
      if (v1 == v2) {
        is_far[i][j] = is_far[j][i] = abs(x2 - x1) >= C;
      } else {
        is_far[i][j] = is_far[j][i] = true;
        // x1 + t * v1 = x2 + t * v2
        // t = (x2 - x1) / (v1 - v2)
        fraction t(x2 - x1, v1 - v2), dt = abs(fraction(C, v2 - v1));
        events.eb(t, 0, min(v1, v2), max(v1, v2), i, j);
        events.eb(t + dt, 1, 0, 0, i, j);
        events.eb(t - dt, 5, 0, 0, i, j);
      }
    }
  }

  vc<bool> is_inside(N);
  rep(i, 0, N) {
    auto [x, v] = pedestrian[i];
    if (v == 0) {
      is_inside[i] = 0 <= x and x <= L;
    } else {
      is_inside[i] = false;
      // x + t * v = 0
      // t = -x / v
      fraction t1(-x, v);
      // x + t * v = L
      // t = (L - x) / v
      fraction t2(L - x, v);
      events.eb(min(t1, t2), 2, 0, 0, i, 0);
      events.eb(max(t1, t2), 4, 0, 0, i, 0);
    }
  }

  rep(i, 0, Q) { events.eb(T[i], 3, 0, 0, i, 0); }

  sort(all(events));

  vi order(N);
  iota(all(order), 0);
  sort(all(order), [&](int a, int b) -> bool {
    auto key = [&](int i) -> pii {
      auto [x, v] = pedestrian[i];
      return {-v, x};
    };
    return key(a) < key(b);
  });

  vi index(N);
  rep(i, 0, N) { index[order[i]] = i; }

  int count = 0;
  auto contribute = [&](int i, int d) -> void {
    if (!(0 <= i and i + 1 < N)) return;
    if (!is_far[order[i]][order[i + 1]]) return;
    if (!is_inside[order[i]]) return;
    if (!is_inside[order[i + 1]]) return;
    count += d;
  };
  auto contribute2 = [&](int i, int d) -> void {
    i = index[i];
    contribute(i, d);
    contribute(i - 1, d);
  };
  auto contribute3 = [&](int i, int j, int d) -> void {
    i = index[i];
    j = index[j];
    if (i > j) {
      swap(i, j);
    }
    contribute(i - 1, d);
    contribute(i, d);
    if (i < j - 1) {
      contribute(j - 1, d);
    }
    contribute(j, d);
  };
  rep(i, 0, N - 1) { contribute(i, 1); }

  vc<bool> ans(Q);
  for (auto [k, t, v1, v2, i, j] : events) {
    if (t == 0) {
      contribute3(i, j, -1);
      swap(order[index[i]], order[index[j]]);
      swap(index[i], index[j]);
      contribute3(i, j, 1);
    } else if (t == 1) {
      contribute3(i, j, -1);
      is_far[i][j] = is_far[j][i] = true;
      contribute3(i, j, 1);
    } else if (t == 5) {
      contribute3(i, j, -1);
      is_far[i][j] = is_far[j][i] = false;
      contribute3(i, j, 1);
    } else if (t == 2) {
      contribute2(i, -1);
      is_inside[i] = true;
      contribute2(i, 1);
    } else if (t == 4) {
      contribute2(i, -1);
      is_inside[i] = false;
      contribute2(i, 1);
    } else if (t == 3) {
      ans[i] = count > 0;
    }
  }

  for (auto e : ans) {
    cout << (e ? 'Y' : 'N') << '\n';
  }
}
