#include <bits/stdc++.h>
using namespace std;

#define int long long
#define float long double
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef pair<float, float> vec;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // tricky?? might be able to get away with a weird bitwise dp

  int N, K;
  cin >> N >> K;

  vc<string> grid(N);
  for (auto &e : grid) cin >> e;

  vi X(K);
  for (auto &e : X) cin >> e;

  int D = 1;
  rep(i, 0, N) { D *= N + 1; }

  auto encode = [&](vi heights) -> int {
    int rv = 0;
    for (auto e : heights) {
      rv = rv * (N + 1) + e;
    }
    return rv;
  };

  auto decode = [&](int x) -> vi {
    vi rv;
    rep(i, 0, N) {
      rv.pb(x % (N + 1));
      x /= N + 1;
    }
    reverse(all(rv));
    return rv;
  };

  auto shift = [&](vi heights) -> vi {
    for (auto &e : heights) {
      e = max(e - 1, 0ll);
    }
    return heights;
  };

  auto check = [&](int i, vi heights) -> bool {
    rep(j, 0, N) {
      if (grid[i][j] == '.') continue;
      if ((grid[i][j] == 'O') != (heights[j] != 0)) return false;
    }
    return true;
  };

  vc dp(N + 1, vc(D, vi(1 << K, 0)));
  dp[0][0][0] = 1;
  rep(i, 0, N) {
    rep(j, 0, K) {
      for (int k = D - 1; k >= 0; k--) {
        auto heights = decode(k);

        for (int l = (1 << K) - 1; l >= 0; l--) {
          if (l >> j & 1) continue;

          if (i + X[j] <= N) {
            rep(m, 0, N) {
              auto heights_ = heights;
              if (heights_[m] != 0) continue;
              heights_[m] = X[j];

              dp[i][encode(heights_)][l | 1 << j] += dp[i][k][l];
            }
          }

          if (X[j] != 1) {
            rep(m, 0, N - X[j] + 1) {
              auto heights_ = heights;
              bool ok = true;
              rep(n, m, m + X[j]) {
                ok = ok and heights_[n] == 0;
                heights_[n] = 1;
              }
              if (!ok) continue;

              dp[i][encode(heights_)][l | 1 << j] += dp[i][k][l];
            }
          }
        }
      }
    }

    rep(j, 0, D) {
      rep(k, 0, 1 << K) {
        auto heights_ = decode(j);
        if (!check(i, heights_)) continue;
        heights_ = shift(heights_);
        dp[i + 1][encode(heights_)][k] += dp[i][j][k];
      }
    }
  }
  cout << dp[N][0][(1 << K) - 1];
}