#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
// #define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vc<int> vi;

const int MAXN = 3e5;
const int MAXM = 3e5;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // max s?

  int N, M;
  cin >> N >> M;

  vc<set<int>> S(N);
  for (auto &r : S) {
    int s;
    cin >> s;
    rep(i, 0, s) {
      int e;
      cin >> e;
      e--;
      r.insert(e);
    }
  }

  vc<vi> adj(N);
  rep(i, 0, N - 1) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }

  vi roots(M, -1);
  rep(i, 0, N) {
    for (auto e : S[i]) {
      roots[e] = i;
    }
  }

  int c = 0;
  for (auto e : S) {
    chmax(c, sz(e));
  }
  bitset<MAXN> is_empty;
  rep(i, 0, N) { is_empty[i] = S[i].empty(); }
  vi ans(M, 0);
  rep(i, 0, c) {
    bitset<MAXN> is_colored;
    while (true) {
      bitset<MAXN> is_unavailable = is_empty | is_colored;
      if (is_unavailable.count() == N) break;
      int r = (~is_unavailable)._Find_first(), s = *S[r].begin();
      ans[s] = i;
      auto dfs = [&](auto self, int a, int p) -> void {
        if (!S[a].contains(s)) return;
        S[a].erase(s);
        if (S[a].empty()) {
          is_empty[a] = true;
        }
        is_colored[a] = true;
        for (auto b : adj[a]) {
          if (b == p) continue;
          self(self, b, a);
        }
      };
      dfs(dfs, r, -1);
    }
  }
  cout << c << '\n';
  for (auto e : ans) {
    cout << e + 1 << ' ';
  }
  cout << '\n';
}
