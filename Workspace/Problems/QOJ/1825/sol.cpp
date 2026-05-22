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

struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  int size(int x) { return -e[find(x)]; }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b], e[b] = a;
    return true;
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

bool dfs(int a, int L, vc<vi> &g, vi &btoa, vi &A, vi &B) {
  if (A[a] != L) return 0;
  A[a] = -1;
  for (int b : g[a])
    if (B[b] == L + 1) {
      B[b] = 0;
      if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
        return btoa[b] = a, 1;
    }
  return 0;
}
int hopcroftKarp(vc<vi> &g, vi &btoa) {
  int res = 0;
  vi A(g.size()), B(btoa.size()), cur, next;
  for (;;) {
    fill(all(A), 0);
    fill(all(B), 0);
    cur.clear();
    for (int a : btoa)
      if (a != -1) A[a] = -1;
    rep(a, 0, sz(g)) if (A[a] == 0) cur.pb(a);
    for (int lay = 1;; lay++) {
      bool islast = 0;
      next.clear();
      for (int a : cur)
        for (int b : g[a]) {
          if (btoa[b] == -1) {
            B[b] = lay;
            islast = 1;
          } else if (btoa[b] != a && !B[b]) {
            B[b] = lay;
            next.pb(btoa[b]);
          }
        }
      if (islast) break;
      if (next.empty()) return res;
      for (int a : next) A[a] = lay;
      cur.swap(next);
    }
    rep(a, 0, sz(g)) res += dfs(a, 0, g, btoa, A, B);
  }
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, R, G;
  cin >> N >> R >> G;

  vc<tuple<int, int, int>> edges(R);
  for (auto &[c, a, b] : edges) {
    cin >> a >> b >> c;
    a--, b--;
  }
  sort(all(edges));

  vc<vi> guards(G);
  for (auto &r : guards) {
    int k;
    cin >> k;
    r.resize(k);
    for (auto &e : r) {
      cin >> e;
      e--;
    }
  }

  vc<vi> g(N);
  rep(i, 0, G) {
    for (auto e : guards[i]) {
      g[e].pb(i);
    }
  }
  vi btoa(G, -1);
  if (hopcroftKarp(g, btoa) != G) {
    cout << "-1\n";
    exit(0);
  }

  int ans = 0;
  UF uf(N);
  for (auto [c, a, b] : edges) {
    a = uf.find(a);
    b = uf.find(b);
    if (a == b) continue;
    if (uf.size(a) < uf.size(b)) {
      swap(a, b);
    }

    auto g2a = g[a], g2b = g[b];
    for (auto e : g[b]) {
      g[a].pb(e);
    }
    sort(all(g[a]));
    g[a].erase(unique(all(g[a])), g[a].end());
    g[b].clear();

    auto btoa2 = btoa;
    auto it1 = find(all(btoa), b);
    if (it1 != btoa.end()) {
      auto it2 = find(all(btoa), a);
      if (it2 == btoa.end()) {
        *it1 = a;
      } else {
        *it1 = -1;
      }
    }

    hopcroftKarp(g, btoa);

    if (count(all(btoa), -1) > 0) {
      g[a] = g2a;
      g[b] = g2b;
      btoa = btoa2;
      continue;
    }

    uf.join(a, b);
    ans += c;
  }

  int count = 0;
  rep(i, 0, N) {
    if (uf.find(i) != i) continue;
    count += 1;
  }
  if (count != G) {
    cout << "-1\n";
  } else {
    cout << ans << '\n';
  }
}
