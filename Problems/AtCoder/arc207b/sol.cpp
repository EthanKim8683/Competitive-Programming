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

  // 1 <= distance <= 2
  //
  // a node can't have more than one leaf
  //
  // 6 is easy: opposites should add up to 7
  // how can we extend this?
  //
  // make it bipartite and match to all but pair
  // how can we extend this?

  int N;
  cin >> N;

  if (N <= 5) {
    cout << "-1\n";
    exit(0);
  }

  auto check = [&](vc<pii> edges) -> bool {
    vc<vi> adj(N + 1);
    for (auto [u, v] : edges) {
      adj[u].pb(v);
      adj[v].pb(u);
    }

    int x = -1;
    rep(i, 1, N + 1) {
      vi dist(N + 1, INF);
      queue<int> q;
      auto push = [&](int a, int d) -> void {
        if (d >= dist[a]) return;
        dist[a] = d;
        q.push(a);
      };
      push(i, 0);
      while (sz(q) > 0) {
        int a = q.front();
        q.pop();
        for (auto b : adj[a]) {
          push(b, dist[a] + 1);
        }
      }

      int sum = 0;
      rep(j, 1, N + 1) {
        if (j == i) continue;
        if (dist[j] > 2) continue;
        sum += j;
      }
      if (x == -1) {
        x = sum;
      } else {
        if (sum != x) return false;
      }
    }
    cerr << '\n';
    return true;
  };

  vc<pii> ans;
  if (N % 2 == 0) {
    rep(i, 1, N / 2 + 1) {
      rep(j, N / 2 + 1, N + 1) {
        if (i + j == N + 1) continue;
        ans.eb(i, j);
      }
    }
  } else {
    rep(i, 1, (N - 1) / 2 + 1) {
      rep(j, (N - 1) / 2 + 1, N + 1) {
        if (i + j == N) continue;
        ans.eb(i, j);
      }
    }
  }

  cout << sz(ans) << '\n';
  for (auto [u, v] : ans) {
    cout << u << ' ' << v << '\n';
  }
  assert(check(ans));
}
