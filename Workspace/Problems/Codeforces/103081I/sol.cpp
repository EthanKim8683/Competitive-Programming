#ifndef L
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

  // start: 2:51
  // thinking done: 2:59
  // target impl time: 5 min
  // initial impl done: 3:04

  // it's like at most logn or something
  //
  // d = furthest distance from a node
  // 2 * d >= d_max
  //
  // E = ceil(log2(d_max))

  int N, M;
  cin >> N >> M;

  vc<vi> adj(N);
  rep(i, 0, M) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].pb(b);
    adj[b].pb(a);
  }

  vi dist(N, INF);
  queue<int> q;
  auto push = [&](int a, int d) -> void {
    if (d >= dist[a]) return;
    dist[a] = d;
    q.push(a);
  };
  push(0, 0);
  while (q.size() > 0) {
    int a = q.front();
    q.pop();
    for (auto b : adj[a]) {
      push(b, dist[a] + 1);
    }
  }
  int d = *max_element(all(dist));
  if (d == INF) {
    cout << -1 << '\n';
    exit(0);
  }
  cout << __lg(4 * d - 1) << '\n';
}
