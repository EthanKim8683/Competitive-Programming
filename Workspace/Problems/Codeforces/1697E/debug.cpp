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

  auto print = [&](pair<int, int> p) -> void {
    cerr << '(' << p.first << ", " << p.second << ')';
  };

  vector<bool> used(N, false), bad(N, false);
  dsu d(N);
  for (auto [dist, edges] : by_dist) {
    cerr << dist << ": ";
    for (auto [a, b] : edges) {
      cerr << '[';
      print(points[a]);
      cerr << ", ";
      print(points[b]);
      cerr << "] ";
      if (used[a] or used[b]) {
        if (!used[a]) bad[d.leader(a)] = true;
        if (!used[b]) bad[d.leader(b)] = true;
        if (d.same(a, b)) bad[d.leader(a)] = true;
        continue;
      }
      bool t = bad[d.leader(a)] or bad[d.leader(b)];
      bad[d.merge(a, b)] = t;
    }
    cerr << '\n';

    for (auto [a, b] : edges) {
      used[a] = used[b] = true;
    }
  }

  map<int, vector<int>> by_leader;
  for (int i = 0; i < N; i++) {
    by_leader[d.leader(i)].push_back(i);
  }

  vector<int> sizes, color(N);
  for (auto [leader, group] : by_leader) {
    if (!bad[leader]) {
      sizes.push_back(group.size());
      for (auto i : group) {
        color[i] = leader;
        print(points[i]);
      }
      cerr << '\n';
    } else {
      for (auto i : group) {
        sizes.push_back(1);
        color[i] = i;
        print(points[i]);
        cerr << '\n';
      }
    }
  }

  for (int a = 0; a < N; a++) {
    for (int b = 0; b < N; b++) {
      for (int c = 0; c < N; c++) {
        if (a == b or b == c or a == c) continue;

        if (color[a] == color[b] and color[b] == color[c]) {
          assert(dist(a, b) == dist(a, c) and dist(a, b) == dist(b, c));
        }
        if (color[a] == color[b] and color[c] != color[a]) {
          print(points[a]);
          cerr << ' ';
          print(points[b]);
          cerr << ' ';
          print(points[c]);
          cerr << '\n';
          assert(dist(a, b) < dist(a, c) and dist(b, a) < dist(b, c));
        }
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
