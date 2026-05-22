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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

bool find(int j, vc<vi> &g, vi &btoa, vi &vis) {
  if (btoa[j] == -1) return 1;
  vis[j] = 1;
  int di = btoa[j];
  for (int e : g[di])
    if (!vis[e] && find(e, g, btoa, vis)) {
      btoa[e] = di;
      return 1;
    }
  return 0;
}
int dfsMatching(vc<vi> &g, vi &btoa) {
  vi vis;
  rep(i, 0, sz(g)) {
    vis.assign(sz(btoa), 0);
    for (int j : g[i])
      if (find(j, g, btoa, vis)) {
        btoa[j] = i;
        break;
      }
  }
  return sz(btoa) - (int) count(all(btoa), -1);
}

vi cover(vc<vi> &g, int n, int m) {
  vi match(m, -1);
  int res = dfsMatching(g, match);
  vc<bool> lfound(n, true), seen(m);
  for (int it : match)
    if (it != -1) lfound[it] = false;
  vi q, cover;
  rep(i, 0, n) if (lfound[i]) q.pb(i);
  while (!q.empty()) {
    int i = q.back();
    q.pop_back();
    lfound[i] = 1;
    for (int e : g[i])
      if (!seen[e] && match[e] != -1) {
        seen[e] = true;
        q.pb(match[e]);
      }
  }
  rep(i, 0, n) if (!lfound[i]) cover.pb(i);
  rep(i, 0, m) if (seen[i]) cover.pb(n + i);
  assert(sz(cover) == res);
  return cover;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vc<vi> adj(N);
  rep(i, 0, M) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }

  string S;
  cin >> S;

  vc<vi> g(N);
  rep(i, 0, N) {
    if (S[i] != '0') continue;
    for (auto e : adj[i]) {
      g[i].pb(e);
    }
  }
  vi color(N, 0);
  for (auto e : cover(g, N, N)) {
    color[e % N] = 1;
  }

  rep(i, 0, N) {
    vc<bool> seen(N, false);
    auto dfs = [&](auto self, int a, int c) -> void {
      if (color[a] == c) return;

      if (seen[a]) return;
      seen[a] = true;

      for (auto b : adj[a]) {
        self(self, b, 1 - c);
      }
    };
    dfs(dfs, i, 1 - color[i]);

    vi counts(2, 0);
    rep(j, 0, N) {
      if (!seen[j]) continue;
      counts[color[j]]++;
    }
    if (counts[0] == counts[1]) {
      rep(j, 0, N) {
        if (!seen[j]) continue;
        color[j] ^= 1;
      }
    }
  }

  int ans = count(all(color), 1);

  vc<vi> g2(N);
  rep(i, 0, N) {
    if (color[i] != 1) continue;
    for (auto b : g[i]) {
      if (color[b] != 1) continue;
      g2[i].pb(b);
    }
  }
  vi btoa(N, -1);
  ans += dfsMatching(g2, btoa);

  cout << ans << '\n';
}
