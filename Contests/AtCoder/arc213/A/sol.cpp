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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, L;
  cin >> N >> L;

  vi C(N);
  vc P(N, vi(L));
  rep(i, 0, N) {
    cin >> C[i];
    for (auto &e : P[i]) {
      cin >> e;
      e--;
    }
  }

  map<vi, int> dist;
  vi Q(L);
  iota(all(Q), 0);
  dist[Q] = 0;
  int dmax = 0;
  while (next_permutation(all(Q))) {
    int d = INF;
    rep(i, 0, L - 1) {
      swap(Q[i], Q[i + 1]);
      if (dist.contains(Q)) {
        chmin(d, dist[Q] + 1);
      }
      swap(Q[i], Q[i + 1]);
    }
    dist[Q] = d;
    chmax(dmax, d);
  }

  vi dp(N, -INF), dp2(N, -INF);
  rep(i, 0, min(dmax, N)) {
    if (dist[P[i]] > i + 1) continue;
    chmax(dp[i], 0);
  }
  if (dmax < N) {
    chmax(dp2[dmax], 0);
  }
  rep(i, 0, N) {
    chmax(dp[i], dp2[i]);
    dp[i] += C[i];
    vi inv(L);
    rep(j, 0, L) { inv[P[i][j]] = j; }
    rep(j, 1, min(dmax, N - i)) {
      vi Q(L);
      rep(k, 0, L) { Q[k] = inv[P[i + j][k]]; }
      if (dist[Q] > j) continue;
      chmax(dp[i + j], dp[i]);
    }
    if (i + dmax < N) {
      chmax(dp2[i + dmax], dp[i]);
    }
    if (i + 1 < N) {
      chmax(dp2[i + 1], dp2[i]);
    }
  }
  cout << max(*max_element(all(dp)), 0ll) << '\n';
}
