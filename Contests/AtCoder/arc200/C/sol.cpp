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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<pii> ranges(N);
    for (auto &[l, r] : ranges) {
      cin >> l >> r;
    }

    vc<vi> adj(N);
    rep(i, 0, N) {
      rep(j, 0, N) {
        auto [l1, r1] = ranges[i];
        auto [l2, r2] = ranges[j];
        if (!(l1 < l2 and r2 < r1)) continue;
        adj[i].pb(j);
      }
    }

    vi degree(N, 0);
    for (auto r : adj) {
      for (auto e : r) {
        degree[e] += 1;
      }
    }
    priority_queue<int> pq;
    auto nudge = [&](int a) -> void {
      if (degree[a] != 0) return;
      pq.push(a);
    };
    rep(i, 0, N) { nudge(i); }
    vi P(N);
    int t = N - 1;
    while (sz(pq) > 0) {
      int a = pq.top();
      pq.pop();
      P[a] = t;
      t--;
      for (auto b : adj[a]) {
        degree[b] -= 1;
        nudge(b);
      }
    }
    for (auto e : P) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}
