#include <bits/stdc++.h>

#include "ethankim8683/data_structures.hpp"

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // construct DSU of graph A, then add edges of graph B; all connecting edges
  // increment the answer

  int N, Q;
  cin >> N >> Q;

  vector<tuple<char, int, int>> queries(Q);
  for (auto &[c, x, y] : queries) {
    cin >> c >> x >> y;
    x--, y--;
    if (x > y) {
      swap(x, y);
    }
  }

  // for (int i = 0; i < Q; i++) {
  //   set<tuple<int, int, char>> edges;
  //   for (int j = 0; j <= i; j++) {
  //     auto [c, a, b] = queries[j];
  //     tuple<int, int, char> key = {a, b, c};
  //     if (edges.contains(key)) {
  //       edges.erase(key);
  //     } else {
  //       edges.insert(key);
  //     }
  //   }

  //   dsu d1(N), d2(N);
  //   int ans = 0;
  //   for (auto [a, b, c] : edges) {
  //     if (c == 'A') {
  //       if (d1.same(a, b) and !d2.same(a, b)) {
  //         ans--;
  //       }
  //       d1.merge(a, b);
  //       d2.merge(a, b);
  //     } else {
  //       if (!d1.same(a, b) and !d2.same(a, b)) {
  //         ans++;
  //       }
  //       d1.merge(a, b);
  //     }
  //   }
  //   cout << ans << '\n';
  // }

  int M = 1 << __lg(2 * Q - 1);

  vector<vector<tuple<char, int, int>>> st(2 * M);
  auto apply = [&](int l, int r, tuple<char, int, int> x) -> void {
    for (l += M, r += M; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        st[l].push_back(x);
        l++;
      }
      if (r & 1) {
        r--;
        st[r].push_back(x);
      }
    }
  };

  map<tuple<char, int, int>, int> lefts;
  for (int i = 0; i < Q; i++) {
    auto x = queries[i];
    if (lefts.contains(x)) {
      apply(lefts[x], i, x);
      lefts.erase(x);
    } else {
      lefts.emplace(x, i);
    }
  }
  for (auto [x, l] : lefts) {
    apply(l, Q, x);
  }

  dsu_with_rollbacks d1(N), d2(N);
  vector<int> ans(M), sum = {0};
  auto dfs = [&](auto self, int i) -> void {
    d1.save();
    d2.save();
    sum.push_back(sum.back());
    for (auto [c, a, b] : st[i]) {
      if (c == 'A') {
        if (d1.same(a, b) and !d2.same(a, b)) {
          sum.back()--;
        }
        d1.merge(a, b);
        d2.merge(a, b);
      } else {
        if (!d1.same(a, b) and !d2.same(a, b)) {
          sum.back()++;
        }
        d1.merge(a, b);
      }
    }
    if (i >= M) {
      ans[i - M] = sum.back();
    } else {
      self(self, i << 1);
      self(self, i << 1 | 1);
    }
    d1.rollback();
    d2.rollback();
    sum.pop_back();
  };
  dfs(dfs, 1);
  for (int i = 0; i < Q; i++) {
    cout << ans[i] << '\n';
  }
}
