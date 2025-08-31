#include <bits/stdc++.h>

#include "atcoder/dsu.hpp"
#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<pair<int, int>> points(N);
  for (auto &[x, y] : points) cin >> x >> y;

  auto dist = [&](int a, int b) -> int {
    auto [x1, y1] = points[a];
    auto [x2, y2] = points[b];
    return abs(x1 - x2) + abs(y1 - y2);
  };

  map<int, vector<pair<int, int>>> by_dist;
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      by_dist[dist(i, j)].push_back({i, j});
    }
  }

  vector<bool> used(N, false);
  dsu d(N);
  for (auto [dist, edges] : by_dist) {
    for (auto [a, b] : edges) {
      if (used[a] or used[b]) continue;
      d.merge(a, b);
    }

    for (auto [a, b] : edges) {
      used[a] = used[b] = true;
    }
  }

  map<int, vector<int>> by_leader;
  for (int i = 0; i < N; i++) {
    by_leader[d.leader(i)].push_back(i);
  }

  vector<int> sizes;
  for (auto [leader, group] : by_leader) {
    bool ok = true;
    for (auto a : group) {
      for (auto b : group) {
        for (int c = 0; c < N; c++) {
          if (a == b or a == c or b == c) continue;
          if (d.leader(c) == leader) {
            ok = ok and dist(a, b) == dist(a, c) and dist(a, c) == dist(b, c);
          } else {
            ok = ok and dist(a, b) < dist(a, c) and dist(a, b) < dist(b, c);
          }
        }
      }
    }

    if (ok) {
      sizes.push_back(group.size());
    } else {
      for (int i = 0; i < group.size(); i++) {
        sizes.push_back(1);
      }
    }
  }

  int K = sizes.size();
  vector dp(K + 1, vector<mint>(N + 1, 0));
  dp[0][0] = 1;
  for (int i = 0; i < K; i++) {
    if (sizes[i] > 1) {
      for (int j = 0; j + sizes[i] <= N; j++) {
        dp[i + 1][j + sizes[i]] += dp[i][j];
      }
    }
    for (int j = 0; j + 1 <= N; j++) {
      dp[i + 1][j + 1] += dp[i][j];
    }
  }
  mint ans = 0;
  for (int i = 1; i <= N; i++) {
    ans += dp[K][i] * binom<mint>(N, i) * fact<mint>(i);
  }
  cout << ans.val() << '\n';
}
