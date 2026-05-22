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

const int MOD = 998244353;
const int INF = 1e9;
const int MAXN = 10;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // state is frontier distance deltas

  vi pows(MAXN + 1);
  pows[0] = 1;
  rep(i, 1, MAXN + 1) { pows[i] = pows[i - 1] * 3; }

  string S;
  int D;
  cin >> S >> D;
  for (auto &e : S) {
    e -= 'A';
  }

  int N = sz(S), M = N + D;

  // auto levenshtein_distance = [&](string s, string t) -> int {
  //   vc dist(sz(s) + 1, vi(sz(t) + 1, INF));
  //   dist[0][0] = 0;
  //   rep(i, 0, sz(s) + 1) {
  //     rep(j, 0, sz(t) + 1) {
  //       if (i < sz(s)) {
  //         chmin(dist[i + 1][j], dist[i][j] + 1);
  //       }
  //       if (j < sz(t)) {
  //         chmin(dist[i][j + 1], dist[i][j] + 1);
  //       }
  //       if (i < sz(s) and j < sz(t)) {
  //         chmin(dist[i + 1][j + 1], dist[i][j] + 1);
  //       }
  //       if (i < sz(s) and j < sz(t) and s[i] == s[j]) {
  //         chmin(dist[i + 1][j + 1], dist[i][j]);
  //       }
  //     }
  //   }
  //   return dist[sz(s)][sz(t)];
  // };

  auto decode = [&](int d0, int mask) -> vi {
    vi rv(N + 1);
    rv[0] = d0;
    rep(i, 1, N + 1) { rv[i] = rv[i - 1] + mask / pows[i - 1] % 3 - 1; }
    return rv;
  };

  auto encode = [&](vi dist) -> pii {
    int d0 = dist[0], mask = 0;
    rep(i, 1, N + 1) { mask += (dist[i] - dist[i - 1] + 1) * pows[i - 1]; }
    return {d0, mask};
  };

  vc dp(M + 1, vc(M + 1, vi(pows[N], 0)));
  dp[0][0][pows[N] - 1] = 1;
  rep(i, 0, M) {
    rep(j, 0, M + 1) {
      rep(k, 0, pows[N]) {
        if (dp[i][j][k] == 0) continue;
        auto dist = decode(j, k);
        rep(l, 0, 26) {
          vi dist2(N + 1, INF);
          rep(m, 0, N + 1) {
            chmin(dist2[m], dist[m] + 1);
            if (m < N) {
              chmin(dist2[m + 1], dist2[m] + 1);
            }
            if (m < N) {
              chmin(dist2[m + 1], dist[m] + 1);
            }
            if (m < N and S[m] == l) {
              chmin(dist2[m + 1], dist[m]);
            }
          }
          auto [j2, k2] = encode(dist2);
          (dp[i + 1][j2][k2] += dp[i][j][k]) %= MOD;
        }
      }
    }
  }
  int ans = 0;
  rep(i, 0, M + 1) {
    rep(j, 0, M + 1) {
      rep(k, 0, pows[N]) {
        auto dist = decode(j, k);
        if (dist[N] != D) continue;
        (ans += dp[i][j][k]) %= MOD;
      }
    }
  }
  cout << ans << '\n';
}
