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

const int MAXD = 26;
const int MAXK = 8;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int K, N;
  cin >> K >> N;
  N--;

  auto binom = [&](int n, int k) -> __int128 {
    if (n < 0 or k < 0 or n - k < 0) return 0;
    __int128 rv = 1;
    rep(i, n - k + 1, n + 1) { rv *= i; }
    rep(i, 1, k + 1) { rv /= i; }
    return rv;
  };

  auto count = [&](int p, vi counts) -> __int128 {
    int K = sz(counts);
    vc dp(1 << K, vc<__int128>(K * (K + 1) / 2 + 1, 0));
    dp[0][0] = 1;
    rep(i, 0, 1 << K) {
      int level = __builtin_popcount(i), length = level * (level + 1) / 2;
      rep(j, 0, K) {
        if (~i >> j & 1) continue;
        length -= counts[j];
      }
      rep(j, 0, length + 1) {
        rep(k, 0, K) {
          if (i >> k & 1) continue;
          int count = level + 1 - counts[k];
          if (count == 0) {
            dp[i | 1 << k][j] += dp[i][j];
          } else if (count > 0) {
            rep(l, 1, count + 1) {
              rep(m, 0, min(j, l) + 1) {
                if (k == p) {
                  dp[i | 1 << k][j - m + (count - 1) - (l - 1) + 1] +=
                      dp[i][j] * binom(j, m) * binom(length - j, (l - 1) - m) *
                      binom(count - 1, l - 1);
                  dp[i | 1 << k][j - m + (count - 1) - (l - 1)] +=
                      dp[i][j] * binom(j, m) * binom(length - j, l - m) *
                      binom(count - 1, l - 1);
                } else {
                  dp[i | 1 << k][j - m + (count - 1) - (l - 1)] +=
                      dp[i][j] * binom(j, m) * binom((length + 1) - j, l - m) *
                      binom(count - 1, l - 1);
                }
              }
            }
          }
        }
      }
    }
    return dp[(1 << K) - 1][0];
  };
  string ans;
  int dmin = 0;
  while (K - dmin > MAXK) {
    rep(i, 0, 2 * (K - dmin) - 1) { ans += (char) ('a' + dmin + i % 2); }
    dmin += 2;
  }
  vi counts(K - dmin, 0), index(MAXD, -1);
  int nz = 0, lb = 0, p = -1;
  while (sz(ans) < K * (K + 1) / 2) {
    int d = -1;
    rep(j, dmin, MAXD) {
      if (j == p) continue;
      bool is_zero = index[j] == -1;
      if (is_zero and nz == K - dmin) continue;
      if (is_zero) {
        index[j] = nz;
        nz += 1;
      }
      counts[index[j]] += 1;
      __int128 ub = lb + count(index[j], counts) *
                             binom((MAXD - dmin) - nz, (K - dmin) - nz);
      if (ub > N) {
        d = j;
        break;
      }
      lb = ub;
      counts[index[j]] -= 1;
      if (is_zero) {
        nz -= 1;
        index[j] = -1;
      }
    }
    if (d == -1) {
      cout << "-1\n";
      exit(0);
    }
    ans += (char) ('a' + d);
    p = d;
  }
  cout << ans << '\n';
}
