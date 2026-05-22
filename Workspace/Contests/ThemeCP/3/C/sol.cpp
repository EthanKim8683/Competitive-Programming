#include <bits/stdc++.h>

#include "ethankim8683/trees.hpp"

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;
  int A_max = *max_element(A.begin(), A.end());

  auto [r, adj] = cartesian_tree<int>(A, less<int>());
  vector<int> contrib(A_max + 1, 0);
  auto dfs = [&](auto self, int a) -> void {
    contrib[A[a]]++;
    for (auto b : adj[a]) {
      contrib[A[a]]--;
      self(self, b);
    }
  };
  dfs(dfs, r);
  i64 ans = 0;
  for (int i = 1; i <= A_max; i++) {
    ans += (i64) contrib[i] * i;
  }

  auto ceil_div = [&](int x, int y) -> int { return (x - 1) / y + 1; };
  vector<vector<pair<int, int>>> events(A_max + 1);
  for (int i = 1; i <= A_max; i++) {
    int q = i, l = 1;
    while (true) {
      int r = i + 1;
      while (l < r) {
        int m = l + (r - l) / 2;
        ceil_div(i, m) < q ? r = m : l = m + 1;
      }
      if (l > i) break;
      events[l].push_back({i, ceil_div(i, l)});
      q = ceil_div(i, l);
    }
  }

  vector<int> from(A_max + 1);
  iota(from.begin(), from.end(), 0);
  for (int k = 1; k <= A_max; k++) {
    for (auto [v, to] : events[k]) {
      ans += (i64) contrib[v] * (to - from[v]);
      from[v] = to;
    }
    cout << ans << ' ';
  }
  cout << '\n';
}
