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

struct hltree {
  int n;
  vi par, dep, tin, head;
  hltree(vc<vi> g, int r) : n(sz(g)), par(n), dep(n), tin(n), head(n) {
    auto dfs = [&](auto self, int a) -> int {
      int s = 1, mx = 0;
      for (int &b : g[a]) {
        erase(g[b], par[b] = a);
        dep[b] = dep[a] + 1;
        int t = self(self, b);
        s += t;
        if (t > mx) swap(b, g[a][0]), mx = t;
      }
      return s;
    };
    par[r] = r, dfs(dfs, r);
    iota(all(head), 0);
    int t = 0;
    auto dfs2 = [&](auto self, int a) -> void {
      tin[a] = t++;
      if (sz(g[a])) head[g[a][0]] = head[a];
      for (auto b : g[a]) self(self, b);
    };
    dfs2(dfs2, r);
  }
  void hl(int a, int b, auto cb) {
    for (;; b = par[head[b]]) {
      if (tin[a] > tin[b]) swap(a, b);
      if (head[a] == head[b]) break;
      cb(tin[head[b]], tin[b] + 1);
    }
    cb(tin[a], tin[b] + 1);
  }
  int lca(int a, int b) {
    while (head[a] != head[b]) {
      int &c = dep[head[a]] > dep[head[b]] ? a : b;
      c = par[head[c]];
    }
    return dep[a] < dep[b] ? a : b;
  }
  int dist(int a, int b) { return dep[a] + dep[b] - 2 * dep[lca(a, b)]; }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // dfs tree
  //
  // add loops using crossedges
  //
  // these are shortest path pairs -> shortest path cycle
  //
  // for so long this problem has seemed impossible to me; i hope i get ac

  int N, M;
  cin >> N >> M;

  vc<pii> edges(M);
  for (auto &[s, t] : edges) {
    cin >> s >> t;
    s--, t--;
  }

  vc<vc<pii>> adj(N);
  rep(i, 0, M) {
    auto [a, b] = edges[i];
    adj[a].eb(b, i);
    adj[b].eb(a, i);
  }

  vi dist(N, INF);
  vc<bool> seen(M, false);
  queue<int> q;
  auto push = [&](int a, int d, int i) -> void {
    if (d >= dist[a]) return;
    dist[a] = d;
    if (i != -1) {
      seen[i] = true;
    }
    q.push(a);
  };
  push(N - 1, 0, -1);
  while (sz(q) > 0) {
    int a = q.front();
    q.pop();
    for (auto [b, i] : adj[a]) {
      push(b, dist[a] + 1, i);
    }
  }

  vc<vi> adj2(N);
  rep(i, 0, M) {
    if (!seen[i]) continue;
    auto [a, b] = edges[i];
    adj2[a].pb(b);
    adj2[b].pb(a);
  }
  hltree ht(adj2, N - 1);

  vi st(2 * N, INF);
  auto apply = [&](int l, int r, int x) -> void {
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
      if (l & 1) chmin(st[l++], x);
      if (r & 1) chmin(st[--r], x);
    }
  };
  auto get = [&](int i) -> int {
    int rv = INF;
    for (i += N; i > 0; i >>= 1) {
      chmin(rv, st[i]);
    }
    return rv;
  };

  rep(i, 0, M) {
    if (seen[i]) continue;
    auto [a, b] = edges[i];
    int c = ht.lca(a, b), x = ht.dep[a] + ht.dep[b] + 1;
    ht.hl(a, c, [&](int l, int r) -> void {
      chmax(l, ht.tin[c] + 1);
      apply(l, r, x);
    });
    ht.hl(b, c, [&](int l, int r) -> void {
      chmax(l, ht.tin[c] + 1);
      apply(l, r, x);
    });
  }
  vi cost(N);
  rep(i, 0, N) { cost[i] = get(ht.tin[i]) - ht.dep[i]; }
  cost[N - 1] = 0;

  auto check = [&](int x) -> bool {
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
      if (dist[a] + cost[a] >= x) continue;
      for (auto [b, i] : adj[a]) {
        push(b, dist[a] + 1);
      }
    }
    return dist[N - 1] + cost[N - 1] >= x;
  };
  int l = 0, r = 2 * N;
  while (l < r) {
    int m = l + (r - l + 1) / 2;
    check(m) ? l = m : r = m - 1;
  }
  cout << (l == 2 * N ? -1 : l) << '\n';
}
