#include <bits/stdc++.h>

#include "atcoder/dsu.hpp"
#include "ethankim8683/trees.hpp"

using namespace std;
using namespace atcoder;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int H, W;
  cin >> H >> W;

  vector F(H, vector<int>(W));
  for (auto &r : F) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  auto encode = [&](int i, int j) -> int { return i * W + j; };
  auto decode = [&](int x) -> pair<int, int> { return {x / W, x % W}; };

  vector<int> order(H * W);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int a, int b) {
    auto [i1, j1] = decode(a);
    auto [i2, j2] = decode(b);
    return F[i1][j1] > F[i2][j2];
  });
  dsu d(H * W);
  vector<vector<int>> adj(H * W);
  vector<int> seen(H * W, false);
  vector<int> leader(H * W);
  iota(leader.begin(), leader.end(), 0);
  for (auto x : order) {
    auto [i, j] = decode(x);
    seen[x] = true;
    for (auto [di, dj] :
         (pair<int, int>[]) {{-1, 0}, {0, -1}, {1, 0}, {0, 1}}) {
      int i_ = i + di, j_ = j + dj;
      if (i_ < 0 or j_ < 0 or i_ >= H or j_ >= W) continue;

      int y = encode(i_, j_);
      if (seen[y] and !d.same(x, y)) {
        auto [u, v] = decode(x);
        auto [p, q] = decode(y);
        adj[x].push_back(leader[d.leader(y)]);
        d.merge(x, y);
      }
      leader[d.leader(x)] = x;
    }
  }
  tree_utils tu(adj, leader[d.leader(0)]);

  int Q;
  cin >> Q;

  for (int i = 0; i < Q; i++) {
    int A, B, Y, C, D, Z;
    cin >> A >> B >> Y >> C >> D >> Z;
    A--, B--, C--, D--;

    auto [U, V] = decode(tu.lca(encode(A, B), encode(C, D)));
    int X = F[U][V];
    cout << Y + Z - 2 * min(X, min(Y, Z)) << '\n';
  }
}
