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

  // start: 1:45
  // thinking done: 2:05
  // target impl time: 20 min
  // initial impl done: 2:19

  int N, M;
  cin >> N >> M;

  vc<string> grid1(N);
  for (auto &e : grid1) cin >> e;

  auto is_winning = [&](int r, int c) -> bool {
    auto grid2 = grid1;
    grid2[r][c] = '#';

    auto encode = [&](int r, int c) -> int { return r * M + c; };
    auto decode = [&](int x) -> pii { return {x / M, x % M}; };
    auto parity = [&](int r, int c) -> int { return (r + c) % 2; };
    auto is_inside = [&](int r, int c) -> bool {
      return 0 <= r and r < N and 0 <= c and c < M;
    };

    vc<vi> g(N * M);
    UF uf(N * M);
    auto add_edge = [&](int r1, int c1, int r2, int c2) -> void {
      assert(parity(r1, c1) != parity(r2, c2));
      if (parity(r1, c1) != 0) {
        swap(r1, r2);
        swap(c1, c2);
      }
      int a = encode(r1, c1), b = encode(r2, c2);
      g[a].pb(b);
      uf.join(a, b);
    };
    rep(i, 0, N) {
      rep(j, 0, M) {
        if (grid2[i][j] != '.') continue;
        if (i + 1 < N and grid2[i + 1][j] == '.') {
          add_edge(i, j, i + 1, j);
        }
        if (j + 1 < M and grid2[i][j + 1] == '.') {
          add_edge(i, j, i, j + 1);
        }
      }
    }

    vi btoa(N * M, -1), atob(N * M, -1);
    hopcroftKarp(g, btoa);
    rep(b, 0, N * M) {
      if (btoa[b] == -1) continue;
      atob[btoa[b]] = b;
    }

    vc counts(N * M, vi(2, 0));
    rep(i, 0, N) {
      rep(j, 0, M) {
        if (grid2[i][j] != '.') continue;
        if (parity(i, j) == 0) {
          int a = encode(i, j);
          if (atob[a] == -1) {
            counts[uf.find(a)][0]++;
          }
        } else {
          int b = encode(i, j);
          if (btoa[b] == -1) {
            counts[uf.find(b)][1]++;
          }
        }
      }
    }

    pii deltas[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (auto [dr, dc] : deltas) {
      int i = r + dr, j = c + dc;
      if (!is_inside(i, j)) continue;
      if (grid2[i][j] != '.') continue;
      if (counts[uf.find(encode(i, j))][parity(i, j)] != 0) return false;
    }
    return true;
  };

  int ans = 0;
  rep(i, 0, N) {
    rep(j, 0, M) {
      if (grid1[i][j] != '.') continue;
      if (!is_winning(i, j)) continue;
      ans++;
    }
  }
  cout << ans << '\n';
}
