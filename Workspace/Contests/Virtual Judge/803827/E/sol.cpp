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

  // based on the counts

  int N;
  cin >> N;

  vc table(N, vi(N));
  for (auto &r : table) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  // determining the location of the 2 determines the location of everything
  // else
  //
  // first fix 2, then that fixes 4, then that fixes 6, ...

  vi counts(N + N + 1, 0);
  for (auto r : table) {
    for (auto e : r) {
      counts[e] += 1;
    }
  }
  vi roots;
  rep(i, 2, N + N + 1) {
    if (counts[i] != 1) continue;
    roots.pb(i);
  }
  auto solve = [&](int x0) -> vc<vi> {
    vi mapping(N + N + 1, N + N), counts(N + N + 1, 0);
    vc<vc<pii>> indices(N + N + 1);
    vc<vi> by_i(N), by_j(N);
    rep(i, 0, N) {
      rep(j, 0, N) {
        counts[table[i][j]] += 1;
        indices[table[i][j]].eb(i, j);
        by_i[i].pb(j);
        by_j[j].pb(i);
      }
    }
    vc seen(N, vc<bool>(N, false));
    queue<int> q;
    q.push(x0);
    int y = 0;
    while (sz(q) > 0) {
      int x = q.front();
      q.pop();
      int i = -1, j;
      for (auto [k, l] : indices[x]) {
        if (seen[k][l]) continue;
        i = k;
        j = l;
      }
      if (i == -1) continue;
      y += 2;
      vc<pii> relevant;
      for (auto k : by_i[i]) {
        relevant.eb(i, k);
      }
      for (auto k : by_j[j]) {
        relevant.eb(k, j);
      }
      for (auto [k, l] : relevant) {
        mapping[table[k][l]] = y + counts[table[k][l]] - 1;
      }
      for (auto [k, l] : relevant) {
        seen[k][l] = true;
        counts[table[k][l]] -= 1;
        if (counts[table[k][l]] == 1) {
          q.emplace(table[k][l]);
        }
      }
      by_i[i].clear();
      by_j[j].clear();
    }
    auto rv = table;
    for (auto &r : rv) {
      for (auto &e : r) {
        e = mapping[e];
      }
    }
    return rv;
  };
  vc<vi> ans;
  for (auto x : roots) {
    auto t = solve(x);
    if (ans.empty() or t < ans) {
      ans = t;
    }
  }
  rep(i, 0, N) {
    if (i > 0) {
      cout << '\n';
    }
    rep(j, 0, N) {
      if (j > 0) {
        cout << ' ';
      }
      cout << ans[i][j];
    }
  }
}
