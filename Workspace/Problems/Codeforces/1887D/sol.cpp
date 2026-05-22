#include <bits/stdc++.h>

#include "ethankim8683/data_structures.hpp"

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  int Q;
  cin >> Q;

  vector<pair<int, int>> queries(Q);
  for (auto &[l, r] : queries) {
    cin >> l >> r;
    l--, r--;
  }

  sparse_table<int> minst(A, INF,
                          [&](int a, int b) -> int { return min(a, b); });
  sparse_table<int> maxst(A, -INF,
                          [&](int a, int b) -> int { return max(a, b); });

  vector<vector<int>> by_l(N), by_r(N);
  for (int i = 0; i < Q; i++) {
    auto [l, r] = queries[i];
    by_l[l].push_back(i);
    by_r[r].push_back(i);
  }
  vector<bool> ans(Q, false);
  auto dfs = [&](auto self, int l, int r) -> void {
    if (l == r) return;

    int m = l + (r - l) / 2;
    self(self, l, m);
    self(self, m + 1, r);

    vector<pair<int, int>> stack;
    for (int i = m - 1; i >= l; i--) {
      int rmax = minst.query(i + 1, m + 1);
      while (stack.size() > 0 and stack.back().first <= A[i]) {
        rmax = max(rmax, stack.back().second);
        stack.pop_back();
      }
      if (A[i] < rmax) {
        stack.push_back({A[i], rmax});
      }

      for (auto j : by_l[i]) {
        auto [L, R] = queries[j];
        if (!(m <= R and R < r)) continue;
        ans[j] = ans[j] or (stack.size() > 0 and
                            stack.back().first < minst.query(m, R + 1));
      }
    }

    stack.clear();
    for (int i = m + 1; i < r; i++) {
      int lmin = maxst.query(m, i);
      while (stack.size() > 0 and stack.back().second >= A[i]) {
        lmin = min(lmin, stack.back().first);
        stack.pop_back();
      }
      if (lmin < A[i]) {
        stack.push_back({lmin, A[i]});
      }

      for (auto j : by_r[i]) {
        auto [L, R] = queries[j];
        if (!(l <= L and L <= m)) continue;
        ans[j] = ans[j] or (stack.size() > 0 and
                            stack.back().second > maxst.query(L, m + 1));
      }
    }
  };
  dfs(dfs, 0, N);

  for (auto e : ans) {
    cout << (e ? "Yes" : "No") << '\n';
  }
}
