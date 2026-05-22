#pragma GCC optimize("trapv")
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
typedef vector<int> vi;

const int INF = 1e9;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, D, Alpha1, Alpha2;
  cin >> N >> D >> Alpha1 >> Alpha2;
  D--;

  vc<vc<pii>> adj(N);
  vc<map<int, int>> angle(N);
  rep(a, 0, N) {
    int M;
    cin >> M;

    rep(_i, 0, M) {
      int b, t, angle_;
      cin >> b >> t >> angle_;
      b--;
      adj[a].eb(b, t);
      angle[a][b] = angle_;
    }
  }

  vc<map<int, int>> dist(N);
  priority_queue<tuple<int, int, int>> pq;
  auto push = [&](int a, int p, int d) -> void {
    if (dist[a].contains(p) and d >= dist[a][p]) return;
    dist[a][p] = d;
    pq.push({-d, a, p});
  };
  auto solve = [&]() -> void {
    while (pq.size() > 0) {
      auto [d, a, p] = pq.top();
      pq.pop();
      if ((d = -d) != dist[a][p]) continue;
      for (auto [b, t] : adj[a]) {
        int alpha = (angle[a][b] - angle[a][p] + 180 + 360) % 360;
        if (alpha <= Alpha1 or alpha >= 360 - Alpha2) {
          push(b, a, d + t);
        }
      }
    }
  };

  for (auto [b, t] : adj[0]) {
    push(b, 0, t);
  }
  solve();
  auto distD = dist[D];
  rep(i, 0, N) { dist[i].clear(); }
  for (auto [p, d] : distD) {
    push(D, p, d);
  }
  solve();
  int ans = INF;
  for (auto [p, d] : dist[0]) {
    ans = min(ans, d);
  }
  if (ans == INF) {
    cout << "impossible";
  } else {
    cout << ans;
  }
}