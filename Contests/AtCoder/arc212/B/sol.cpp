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

  int N, M;
  cin >> N >> M;

  vc<tuple<int, int, int>> ops(M);
  for (auto &[x, y, c] : ops) {
    cin >> x >> y >> c;
    x--, y--;
  }

  vc<vc<pii>> adj(M + N);
  rep(i, 0, M) {
    auto [x, y, c] = ops[i];
    adj[i].eb(M + x, c);
    adj[M + y].eb(i, 0);
  }

  vi dist(M + N, INF);
  priority_queue<pii> pq;
  auto push = [&](int a, int d) -> void {
    if (d >= dist[a]) return;
    dist[a] = d;
    pq.emplace(-d, a);
  };
  for (auto [b, w] : adj[0]) {
    push(b, w);
  }
  while (sz(pq) > 0) {
    auto [d, a] = pq.top();
    pq.pop();
    if ((d = -d) != dist[a]) continue;
    for (auto [b, w] : adj[a]) {
      push(b, d + w);
    }
  }
  cout << (dist[0] == INF ? -1 : dist[0]) << '\n';
}
