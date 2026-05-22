#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"

using namespace std;
using namespace atcoder;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M, K;
    cin >> N >> M >> K;

    vector<string> grid(N);
    for (auto &e : grid) cin >> e;

    vector rows(N, fenwick_tree<int>(M)), cols(M, fenwick_tree<int>(N));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (grid[i][j] == '#') {
          rows[i].add(j, 1);
          cols[j].add(i, 1);
        }
      }
    }
    auto clear = [&](int i, int j) -> void {
      if (grid[i][j] == '#') {
        rows[i].add(j, -1);
        cols[j].add(i, -1);
        grid[i][j] = '.';
      }
    };
    auto clear_row = [&](int i, int j) -> void {
      for (int k = j; k < j + K; k++) {
        clear(i, k);
      }
    };
    auto clear_col = [&](int i, int j) -> void {
      for (int k = i; k < i + K; k++) {
        clear(k, j);
      }
    };

    for (int i = 0; i + K <= N; i++) {
      for (int j = 0; j + K <= M; j++) {
        bool r1 = rows[i].sum(j, j + K) == K,
             r2 = rows[i + K - 1].sum(j, j + K) == K,
             c1 = cols[j].sum(i, i + K) == K,
             c2 = cols[j + K - 1].sum(i, i + K) == K;
        if (r1 and c1 and c2) {
          clear_row(i, j);
          clear_col(i, j);
          clear_col(i, j + K - 1);
        } else if (r2 and c1 and c2) {
          clear_row(i + K - 1, j);
          clear_col(i, j);
          clear_col(i, j + K - 1);
        } else if (c1 and r1 and r2) {
          clear_col(i, j);
          clear_row(i, j);
          clear_row(i + K - 1, j);
        } else if (c2 and r1 and r2) {
          clear_col(i, j + K - 1);
          clear_row(i, j);
          clear_row(i + K - 1, j);
        }
      }
    }
    bool ans = true;
    for (auto r : grid) {
      for (auto e : r) {
        ans = ans and e == '.';
      }
    }
    cout << (ans ? "yes" : "no") << '\n';
  }
}
