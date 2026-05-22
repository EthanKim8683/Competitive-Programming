#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "ethankim8683/data_structures.hpp"
using namespace ethankim8683;

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

  int N, Q;
  cin >> N >> Q;

  vc counts(N, vi(2, 0));
  rep(i, 0, N) { counts[i][0] = 1; }
  using S = int;
  auto op = [&](S a, S b) -> S { return a ^ b; };
  auto inv = [&](S x) -> S { return x; };
  dsu_with_potentials<S, op, inv> d(N, 0);
  bool ok = true;
  int ans = 0;
  while (Q--) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    int a = d.leader(u), b = d.leader(v);
    if (a == b) {
      ok = ok and d.merge(u, v, 1);
    } else {
      ans -= min(counts[a][0], counts[a][1]);
      ans -= min(counts[b][0], counts[b][1]);
      int x = d.potential(u) ^ d.potential(v) ^ 1;
      d.merge(u, v, 1);
      if (d.leader(a) != a) {
        swap(a, b);
      }
      rep(i, 0, 2) { counts[a][i] += counts[b][i ^ x]; }
      ans += min(counts[a][0], counts[a][1]);
    }
    cout << (ok ? ans : -1) << '\n';
  }
}
