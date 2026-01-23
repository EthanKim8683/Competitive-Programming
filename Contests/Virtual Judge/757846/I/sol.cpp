#include <queue>
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

  int N, M, A, B;
  cin >> N >> M >> A >> B;
  A--, B--;

  vc<tuple<int, int, int>> edges(M);
  for (auto &[i1, i2, l] : edges) {
    cin >> i1 >> i2 >> l;
    i1--, i2--;
  }

  vc<vc<pii>> adj(N);
  for (auto [i1, i2, l] : edges) {
    adj[i1].push_back({i2, l});
    adj[i2].push_back({i1, l});
  }

  vc dist(2, vi(N, INF));
  priority_queue<tuple<int, int, int>> pq;
  auto push = [&](int i, int a, int d) -> void {
    if (d >= dist[i][a]) return;
    dist[i][a] = d;
    pq.push({-d, i, a});
  };
  push(0, A, 0);
  push(1, B, 0);
  while (pq.size() > 0) {
    auto [d, i, a] = pq.top();
    pq.pop();
    if ((d = -d) != dist[i][a]) continue;
    for (auto [b, l] : adj[a]) {
      push(i, b, d + l);
    }
  }

  int ans = 0;
  for (auto [i1, i2, l] : edges) {
    if (min(dist[0][i1] + l + dist[1][i2], dist[1][i1] + l + dist[0][i2]) !=
        dist[0][B]) {
      ans += l;
    }
  }
  cout << ans;
}