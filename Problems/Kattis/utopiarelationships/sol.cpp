#pragma GCC optimize("Ofast,unroll-loops")
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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

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

  auto sign = [&](int x) -> int { return (x > 0) - (x < 0); };

  vi sum(N, 0);
  vc points(N, vi(N, 0));
  while (count(all(sum), 2) < N) {
    vc seen(N, vc<bool>(2, false));
    auto dfs = [&](auto self, int a, int d) -> bool {
      if (seen[a][d == 1]) return false;
      seen[a][d == 1] = true;

      if (sign(2 - sum[a]) == -d) return true;

      for (auto b : adj[a]) {
        points[a][b] += d;
        points[b][a] += d;
        if (0 <= points[a][b] and points[a][b] <= 2 and self(self, b, -d)) {
          sum[a] += d;
          sum[b] += d;
          return true;
        }
        points[a][b] -= d;
        points[b][a] -= d;
      }
      return false;
    };
    bool ok = false;
    rep(j, 0, N) {
      if (sum[j] == 2) continue;
      if (dfs(dfs, j, sign(2 - sum[j]))) {
        ok = true;
        break;
      }
    }
    if (!ok) {
      cout << -1 << '\n';
      exit(0);
    }
  }

  for (auto r : points) {
    for (auto e : r) {
      cout << e * 5000 << ' ';
    }
    cout << '\n';
  }
}
