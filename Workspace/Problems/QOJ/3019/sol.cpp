#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define double long double
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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

struct Frac {
  ll p, q;
};

template <class F>
Frac fracBS(F f, ll N, ll M) {
  bool dir = 1, A = 1, B = 1;
  Frac lo{0, 1}, hi{1, 0};
  if (f(lo)) return lo;
  assert(f(hi));
  while (A || B) {
    ll adv = 0, step = 1;
    for (int si = 0; step; (step *= 2) >>= si) {
      adv += step;
      Frac mid{lo.p * adv + hi.p, lo.q * adv + hi.q};
      if (abs(mid.p) > N || mid.q > M || dir == !f(mid)) {
        adv -= step;
        si = 2;
      }
    }
    hi.p += lo.p * adv;
    hi.q += lo.q * adv;
    dir = !dir;
    swap(lo, hi);
    A = B;
    B = !!adv;
  }
  return dir ? hi : lo;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M, Q;
  cin >> N >> M >> Q;

  auto count = [&](Frac f, bool le) -> int {
    auto [p, q] = f;
    if (p == 0) return le ? M - 1 : 0;
    if (q == 0) return le ? N * M - 1 : N * (M - 1);
    int n = N - 1, m = M - 1, rv = 0;
    if (!le) {
      rv -= min(n / p, m / q);
    }
    while (m > 0) {
      auto [q2, p2] = fracBS(
          [&](Frac f2) -> bool {
            auto [q2, p2] = f2;
            if (q2 == 0) return false;
            if (p2 == 0) return true;
            return q2 * p >= q * p2;
          },
          m, n);
      int d = INF;
      if (p2 != 0) {
        chmin(d, n / p2);
      }
      if (q2 != 0) {
        chmin(d, m / q2);
      }
      rv += ((d * p2 + 1) * (d * q2 + 1) - (d + 1)) / 2;
      rv += d;
      rv += (d * p2) * (m - d * q2);
      n -= d * p2;
      m -= d * q2;
    }
    return rv;
  };

  while (Q--) {
    int i;
    cin >> i;
    i--;
    auto f = fracBS([&](Frac f) -> bool { return count(f, true) > i; }, N - 1,
                    M - 1);
    auto [p, q] = f;
    int d = i - count(f, false) + 1;
    cout << 1 + d * p << ' ' << 1 + d * q << '\n';
  }
}
