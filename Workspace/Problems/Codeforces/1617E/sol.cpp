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

  unordered_map<int, top_two<pair<int, int>, int>> tt;
  tuple<int, int, int> ans = {0, -1, -1};
  int t = -1;
  for (int i = 0; i < N; i++) {
    auto flip = [&](int x) -> int { return (1 << __lg(2 * x - 1)) - x; };
    map<int, pair<int, int>> adj;
    for (int j = 0; j <= 30; j++) {
      int x = A[i] & ((1 << j) - 1), p = t--, d = 0;
      for (int k = A[i]; k > x; p = k, k = flip(k), d++);
      adj[x] = {p, d};
    }
    for (int j = 2; j <= 30; j++) {
      int x = flip(A[i]) & ((1 << j) - 1), p = t--, d = 0;
      for (int k = A[i]; k > x; p = k, k = flip(k), d++);
      adj[x] = {p, d};
    }
    for (auto [x, y] : adj) {
      if (!tt.contains(x)) continue;
      auto [p, d] = y;
      auto [d2, j] = tt[x].first.from == p ? tt[x].second.val : tt[x].first.val;
      ans = max(ans, {d + d2, j, i});
    }

    for (auto [x, y] : adj) {
      auto [p, d] = y;
      if (!tt.contains(x)) {
        tt[x] = top_two<pair<int, int>, int>(
            {-INF, -1}, -INF, [&](auto a, auto b) { return a > b; });
      }
      tt[x].put({d, i}, p);
    }
  }
  auto [m, x, y] = ans;
  cout << x + 1 << ' ' << y + 1 << ' ' << m;
}
