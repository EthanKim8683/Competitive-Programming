#ifndef L
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
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

const double INF = 1e30;
const int K = 200;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 1:14
  // thinking done: 1:22
  // target impl time: 15 min
  // initial impl done: 1:32

  // it might be that a strategy has a bad expected value, but it can avoid
  // large investment easily
  // dp[levels done][time taken] = expected time
  // binary search?

  int N, T, S;
  cin >> N >> T >> S;

  vc<array<int, 6>> levels(N);
  for (auto &r : levels) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  auto solve = [&](double e) -> double {
    vc dp(N, vc<double>(T));
    for (int i = N - 1; i >= 0; i--) {
      rep(j, 0, T) {
        auto f = [&](int x) -> double {
          if (j + x >= T) return j + e;
          if (i + 1 == N) return j + min((double) x, e);
          return min(dp[i + 1][j + x], j + e);
        };
        auto [P1, G1, B1, P2, G2, B2] = levels[i];
        double p1 = (double) P1 / 100, p2 = (double) P2 / 100;
        dp[i][j] =
            min(p1 * f(G1) + (1 - p1) * f(B1), p2 * f(G2) + (1 - p2) * f(B2));
      }
    }
    return dp[0][S];
  };
  double l = 0, r = INF;
  rep(i, 0, K) {
    double m = (l + r) / 2;
    solve(m) < m ? r = m : l = m;
  }
  cout << setprecision(14) << fixed << (l + r) / 2 << '\n';
}
