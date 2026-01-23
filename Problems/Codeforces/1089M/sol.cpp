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

struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
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

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vc adj(N, vc<int>(N));
  for (auto &r : adj) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  rep(i, 0, N) {
    vc<int> seen(N, 0);
    auto dfs = [&](auto self, int a) -> void {
      if (seen[a]) return;
      seen[a] = 1;

      rep(b, 0, N) {
        if (adj[a][b] == 0) continue;
        self(self, b);
      }
    };
    dfs(dfs, i);
    adj[i] = seen;
  }

  UF uf(N);
  rep(i, 0, N) {
    rep(j, 0, N) {
      if (adj[i][j] == 1 and adj[j][i] == 1) {
        uf.join(i, j);
      }
    }
  }

  vi roots;
  rep(i, 0, N) {
    if (i != uf.find(i)) continue;
    roots.pb(i);
  }

  vc<bool> seen(N, false);
  vi order;
  auto dfs = [&](auto self, int a) -> void {
    if (seen[a]) return;
    seen[a] = true;

    for (auto b : roots) {
      if (adj[a][b] == 0) continue;
      self(self, b);
    }
    order.pb(a);
  };
  for (auto e : roots) {
    dfs(dfs, e);
  }
  reverse(all(order));

  vi layer(N);
  rep(i, 0, sz(order)) { layer[order[i]] = i; }

  vc<pii> edges;
  for (auto e : roots) {
    for (auto e2 : roots) {
      if (e != e2 and adj[e][e2] == 1) {
        edges.eb(e, e2);
      }
    }
  }

  int A = 20, B = 3, C = 72;

  vc field(A, vc(B, vc<char>(C, '.')));
  for (int i = 2; i < A; i += 2) {
    rep(j, 0, C) { field[i][0][j] = '#'; }
  }

  vi shift(A, 0);
  rep(i, 0, N) {
    int j = layer[uf.find(i)];
    field[1 + 2 * j][0][shift[j]++] = '1' + i;
  }

  rep(i, 0, sz(edges)) {
    rep(j, 0, A) { field[j][1][2 * i] = '#'; }
    auto [a, b] = edges[i];
    field[1 + 2 * layer[a]][1][2 * i] = '.';
    field[1 + 2 * layer[b]][1][2 * i] = '.';
    field[2 + 2 * layer[b]][2][2 * i] = '#';
  }

  cout << C << ' ' << B << ' ' << A << '\n';
  for (auto g : field) {
    for (auto r : g) {
      for (auto e : r) {
        cout << e;
      }
      cout << '\n';
    }
    cout << '\n';
  }
}
