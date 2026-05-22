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

const int LOGX = 61;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // basically, they use simple approximations of a solution to create bounds
  // and the bounds lead to cases we can prove
  //
  // this helps when the problem is really abstract but there are simple
  // approximations to solve it
  //
  // or maybe in general just come up with half-solutions, then treat them as
  // observations when they don't work

  int T;
  cin >> T;

  while (T--) {
    int Q, L, R;
    cin >> Q >> L >> R;

    auto lt = [&](int x) -> vi {
      vc dp(LOGX + 1, vc(2, vi(2, 0)));
      dp[0][0][1] = 1;
      rep(i, 0, LOGX) {
        rep(j, 0, 2) {
          rep(k, 0, 2) {
            rep(l, 0, 2) {
              int lmax = x >> (LOGX - 1 - i) & 1;
              if (k == 1 and l > lmax) break;
              dp[i + 1][(j + l) % 2][k == 1 and l == lmax ? 1 : 0] +=
                  dp[i][j][k];
            }
          }
        }
      }
      vi rv(2, 0);
      rep(i, 0, 2) { rv[i] += dp[LOGX][i][0]; }
      return rv;
    };
    auto add = lt(R + 1), subtract = lt(L);
    pii best = {0, -1};
    rep(i, 0, 2) { chmax(best, pii{add[i] - subtract[i], i}); }
    auto [ans, p] = best;
    if (Q == 0) {
      cout << ans << '\n';
    } else {
      rep(i, L, R + 1) {
        cout << (__builtin_popcountll(i) % 2 == p ? '1' : '0');
      }
      cout << '\n';
    }
  }
}
