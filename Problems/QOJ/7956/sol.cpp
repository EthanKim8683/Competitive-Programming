#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

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

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vi S(N);
  for (auto &e : S) cin >> e;

  vi T(N);
  for (auto &e : T) cin >> e;

  auto key = [&](vi S) -> vi {
    sort(all(S));
    return S;
  };
  if (key(S) != key(T)) {
    cout << "-1\n";
    exit(0);
  }

  auto solve = [&](vi S, vi T) -> int {
    static vc dp(N, vc(2, vc(2, INF)));
    int rv = INF;
    rep(i, 0, N) {
      dp[0][0][0] = i * N;
      rep(j, 0, N) {
        rep(k, 0, 2) {
          rep(l, 0, 2) {
            if (dp[j][k][l] == INF) continue;
            if (j + 1 < N and S[j + k] == T[(i + j + l) % N]) {
              chmin(dp[j + 1][k][l], dp[j][k][l]);
            }
            if (k + 1 < 2) {
              int cost = dp[j][k][l];
              cost += j;
              if (i == 0 and l == 0) {
                cost = INF;
              }
              chmin(dp[j][k + 1][l], cost);
            }
            if (l + 1 < 2) {
              int cost = dp[j][k][l];
              if ((i + j) % N < i) {
                cost -= N;
              }
              cost -= (i + j) % N;
              chmin(dp[j][k][l + 1], cost);
            }
            if (j == N - 1 and k == 1 and l == 1) {
              chmin(rv, dp[j][k][l]);
            }
            dp[j][k][l] = INF;
          }
        }
      }
    }
    return rv;
  };
  int ans =
      min(solve(S, T), solve({S.rbegin(), S.rend()}, {T.rbegin(), T.rend()}));
  cout << (ans == INF ? -1 : ans) << '\n';
}
