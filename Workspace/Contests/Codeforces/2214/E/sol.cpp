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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vc dist(N, vi(N, INF));
  rep(i, 0, M) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    dist[u][v] = dist[v][u] = w;
  }

  rep(i, 0, N) {
    rep(k, 0, N) {
      rep(j, 0, N) { chmin(dist[i][j], dist[i][k] + dist[k][j]); }
    }
  }
  rep(i, 1, N) { cout << (dist[0][i] == INF ? -1 : dist[0][i]) << '\n'; }
}
