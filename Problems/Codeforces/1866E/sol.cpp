#include <bits/stdc++.h>

#include "atcoder/segtree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

const i64 INF = 1e18;

int op(int a, int b) { return min(a, b); }
int e() { return 1e5; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, Q;
  cin >> N >> Q;

  vector<int> A(Q + 1);
  for (int i = 1; i <= Q; i++) {
    cin >> A[i];
  }

  vector<array<int, 3>> queries(Q + 1);
  for (int i = 1; i <= Q; i++) {
    auto &[t, u, v] = queries[i];
    cin >> t;
    if (t == 1) {
      cin >> u >> v;
    } else {
      cin >> u;
      u--;
    }
  }

  vector dp(2, vector(Q + 1, vector(Q + 1, vector<i64>(3, INF))));
  for (int i = 0; i < 3; i++) {
    dp[1][0][0][i] = 0;
  }
  array<bool, 3> off = {false};
  vector<int> pos(Q + 1);
  pos[0] = 1;
  vector st(3, segtree<int, op, e>(Q + 1));
  auto chmin = [&](i64 &a, i64 b) -> void { a = min(a, b); };
  int n = 0;
  for (int i = 1; i <= Q; i++) {
    auto [t, u, v] = queries[i];
    if (t == 1) {
      pos[i] = v;
    } else {
      off[u] = !off[u];
    }
    for (int j = 0; j < 3; j++) {
      if (off[j]) continue;
      st[j].set(i, A[i]);
    }
    for (int j = 0; j < i; j++) {
      for (int k = 0; k < i; k++) {
        for (int l = 0; l < 3; l++) {
          if (t == 1) {
            auto E = (array<int, 3>[]) {{n, j, k}, {j, n, k}, {j, k, n}}[l];
            for (int m = 0; m < 3; m++) {
              if (off[m]) continue;
              auto [j_, k_] = (array<int, 2>[]) {
                  {E[1], E[2]}, {E[0], E[2]}, {E[0], E[1]}}[m];
              chmin(dp[(i + 1) % 2][j_][k_][m],
                    dp[i % 2][j][k][l] +
                        (i64) st[m].prod(E[m], i + 1) * abs(u - pos[E[m]]) +
                        (i64) A[i] * abs(v - u));
            }
          } else {
            dp[(i + 1) % 2][j][k][l] = dp[i % 2][j][k][l];
          }
          dp[i % 2][j][k][l] = INF;
        }
      }
    }
    if (t == 1) {
      n = i;
    }
  }
  i64 ans = INF;
  for (auto t : dp[(Q + 1) % 2]) {
    for (auto r : t) {
      for (auto e : r) {
        ans = min(ans, e);
      }
    }
  }
  cout << ans;
}
