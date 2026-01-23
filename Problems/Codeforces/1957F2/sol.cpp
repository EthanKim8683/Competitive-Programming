#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"
#include "atcoder/modint.hpp"
#include "ethankim8683/tree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;
using mint = modint;

const int MAXN = 1e5;
const int LOGN = __lg(MAXN) + 1;
const int MAXA = 1e5;
const int MAXK = 10;
const int BASE = 696969;
const int MOD = (1ll << 31) - 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  mint::set_mod(MOD);

  vector<mint> pows(MAXA);
  pows[0] = 1;
  for (int i = 1; i < MAXA; i++) {
    pows[i] = pows[i - 1] * BASE;
  }

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) {
    cin >> e;
    e--;
  }

  vector<vector<int>> adj(N);
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int Q;
  cin >> Q;

  vector<array<int, 5>> queries(Q);
  for (auto &[u1, v1, u2, v2, k] : queries) {
    cin >> u1 >> v1 >> u2 >> v2 >> k;
    u1--, v1--, u2--, v2--;
  }

  vector<vector<int>> by_A(MAXA);
  for (int i = 0; i < N; i++) {
    by_A[A[i]].push_back(i);
  }

  tree_utils tu(adj, 0);
  vector<array<int, 6>> queries2(Q);
  for (int i = 0; i < Q; i++) {
    auto [u1, v1, u2, v2, k] = queries[i];
    queries2[i] = {u1, v1, tu.lca(u1, v1), u2, v2, tu.lca(u2, v2)};
  }

  auto hash = [&](vector<int> colors) -> vector<mint> {
    vector<vector<int>> by_color(MAXA + 1);
    for (int i = 0; i < Q; i++) {
      by_color[colors[i]].push_back(i);
    }

    vector<mint> rv(Q, 0);
    fenwick_tree<mint> ft(N + 1);
    auto hash = [&](int u, int v, int w) -> mint {
      mint rv = 0;
      rv += ft.sum(0, tu.get_index(u) + 1);
      rv += ft.sum(0, tu.get_index(v) + 1);
      rv -= ft.sum(0, tu.get_index(w) + 1);
      if (w != 0) {
        rv -= ft.sum(0, tu.get_index(tu.get_parent(w)) + 1);
      }
      return rv;
    };
    for (int i = 0; i < MAXA; i++) {
      for (auto e : by_A[i]) {
        auto [l, r] = tu.get_range(e);
        ft.add(l, pows[i]);
        ft.add(r, -pows[i]);
      }

      for (auto e : by_color[i]) {
        auto [u1, v1, w1, u2, v2, w2] = queries2[e];
        rv[e] = hash(u1, v1, w1) - hash(u2, v2, w2);
      }
    }
    return rv;
  };

  vector<vector<int>> ans(Q);
  vector<pair<int, int>> ranges(Q, {0, MAXA});
  vector<mint> bases(Q, 0);
  for (int i = 0; i < MAXK; i++) {
    for (auto &[l, r] : ranges) {
      r = MAXA;
    }
    for (int j = 0; j < LOGN; j++) {
      vector<int> colors(Q, MAXA);
      for (int k = 0; k < Q; k++) {
        auto [l, r] = ranges[k];
        if (l == r) continue;
        colors[k] = l + (r - l) / 2;
      }

      auto hashes = hash(colors);
      for (int k = 0; k < Q; k++) {
        auto &[l, r] = ranges[k];
        if (l == r) continue;
        int m = colors[k];
        hashes[k] - bases[k] != 0 ? r = m : l = m + 1;
      }
    }

    for (int j = 0; j < Q; j++) {
      auto [l, r] = ranges[j];
      if (l == MAXA) continue;
      ans[j].push_back(l);
    }

    vector<int> colors(Q);
    for (int j = 0; j < Q; j++) {
      auto [l, r] = ranges[j];
      colors[j] = l;
    }
    bases = hash(colors);
  }

  for (int i = 0; i < Q; i++) {
    auto [u1, v1, u2, v2, k] = queries[i];
    if (ans[i].size() > k) {
      ans[i].resize(k);
    }

    cout << ans[i].size();
    for (auto e : ans[i]) {
      cout << ' ' << e + 1;
    }
    cout << '\n';
  }
}
