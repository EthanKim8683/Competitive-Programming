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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int K, N, L;
  cin >> K >> N >> L;

  vi R(N);
  for (auto &e : R) cin >> e;

  auto less = [&](pii x, pii y) -> bool {
    auto [a1, b1] = x;
    auto [a2, b2] = y;
    return (a1 * b2 < a2 * b1) ^ (b1 < 0) ^ (b2 < 0);
  };

  auto solve = [&](int x) -> pii {
    int n = 0;
    rep(i, L, N) {
      while (n <= i and R[i - n] - R[i] < x) {
        n++;
      }
      if (n > L) return {0, 1};
    }

    vi heads;
    rep(i, 0, L) {
      if (R[i - sz(heads)] - R[i] < x or sz(heads) + L - i == n) {
        heads.pb(R[i]);
      }
    }

    if (sz(heads) == 1) return {1, 0};
    sort(all(heads));
    int d = K;
    rep(i, 0, sz(heads)) {
      if (i >= sz(heads) - 2) {
        d -= heads[i];
      } else {
        d -= 2 * heads[i];
      }
    }
    return {d, sz(heads) - 1};
  };

  auto check = [&](int x) -> bool { return !less(solve(x), {x, 1}); };

  int l = 0, r = K;
  while (l < r) {
    int m = l + (r - l + 1) / 2;
    check(m) ? l = m : r = m - 1;
  }

  pii x = {l, 1}, y = solve(l + 1);
  if (less(x, y)) {
    x = y;
  }

  auto [a, b] = x;
  int g = gcd(a, b);
  a /= g;
  b /= g;

  if (b == 1) {
    cout << a << '\n';
  } else {
    cout << a << '/' << b << '\n';
  }
}
