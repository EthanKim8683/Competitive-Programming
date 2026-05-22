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

  int N, M, Q;
  cin >> N >> M >> Q;

  using S = int;
  auto op = [&](int a, int b) -> int { return a + b; };
  auto e = [&]() -> int { return 0; };
  vc psts(N, persistent_segtree<S, op, e>(M));
  while (Q--) {
    int t;
    cin >> t;

    if (t == 1) {
      int x, y;
      cin >> x >> y;
      x--, y--;

      psts[x] = psts[y];
    } else if (t == 2) {
      int x, y, z;
      cin >> x >> y >> z;
      x--, y--;

      psts[x] = psts[x].set(y, z);
    } else if (t == 3) {
      int x, l, r;
      cin >> x >> l >> r;
      x--, l--;

      cout << psts[x].prod(l, r) << '\n';
    }
  }
}
