#pragma GCC optimize("trapv")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define i32 int32_t
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vector<int> vi;

const i32 FLAG = 1u << 30;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N = 4;

  vc used(N, vc<bool>(N, false));
  int count = 0;
  auto dfs = [&](auto self, int d) -> void {
    count++;
    if (d == 20) return;
    rep(i, 0, N) {
      rep(j, 0, N) {
        rep(k, 1, min(N - i, N - j)) {
          bool ok = true;
          rep(l, i, i + k) { ok = ok and !used[l][j + k - 1]; }
          rep(l, j, j + k) { ok = ok and !used[i + k - 1][l]; }
          if (!ok) break;
          rep(l, i, i + k) { used[l][j + k - 1] = true; }
          rep(l, j, j + k) { used[i + k - 1][l] = true; }
          self(self, d + 1);
          rep(l, i, i + k) { used[l][j + k - 1] = false; }
          rep(l, j, j + k) { used[i + k - 1][l] = false; }
        }
      }
    }
  };
  dfs(dfs, 0);
  cerr << count << '\n';

  // int N, M;
  // cin >> N >> M;

  // vc<string> grid(N);
  // for (auto &e : grid) cin >> e;

  // vc ps(2, vc(N + 1, vi(M + 1, 0)));
  // rep(i, 0, N) {
  //   rep(j, 0, M) {
  //     if (grid[i][j] == '$') {
  //       ps[0][i + 1][j + 1] += 1;
  //     }
  //     if (grid[i][j] == '#') {
  //       ps[1][i + 1][j + 1] += 1;
  //     }
  //   }
  // }
  // rep(i, 0, 2) {
  //   rep(j, 1, N + 1) {
  //     rep(k, 1, M + 1) {
  //       ps[i][j][k] += ps[i][j - 1][k] + ps[i][j][k - 1] - ps[i][j - 1][k -
  //       1];
  //     }
  //   }
  // }
  // auto query = [&](int i, int l1, int r1, int l2, int r2) -> int {
  //   return ps[i][r1][r2] - ps[i][l1][r2] - ps[i][r1][l2] + ps[i][l1][l2];
  // };

  // vc dp(N + 1, vc(M + 1, vc(N, vc<i32>(M, -1))));
  // rep(i, 1, N + 1) {
  //   rep(j, 1, M + 1) {
  //     rep(k, 0, N + 1 - i) {
  //       rep(l, 0, M + 1 - j) {
  //         if (i == j and query(0, k, k + i, l, l + j) == 1 and
  //             query(1, k, k + i, l, l + j) == 0) {
  //           dp[i][j][k][l] = -2;
  //           continue;
  //         }
  //         if (query(1, k, k + i, l, l + j) == i * j) {
  //           dp[i][j][k][l] = -3;
  //           continue;
  //         }
  //         rep(m, 1, i) {
  //           if (dp[m][j][k][l] != -1 and dp[i - m][j][k + m][l] != -1) {
  //             dp[i][j][k][l] = m;
  //           }
  //         }
  //         rep(m, 1, j) {
  //           if (dp[i][m][k][l] != -1 and dp[i][j - m][k][l + m] != -1) {
  //             dp[i][j][k][l] = FLAG | m;
  //           }
  //         }
  //       }
  //     }
  //   }
  // }

  // if (dp[N][M][0][0] == -1) {
  //   cout << "elgnatcer";
  //   exit(0);
  // }

  // vc ans(N, vi(M, -1));
  // int t = 0;
  // auto dfs = [&](auto self, int i, int j, int k, int l) -> void {
  //   int v = dp[i][j][k][l];

  //   if (v == -2) {
  //     rep(m, k, k + i) {
  //       rep(n, l, l + j) { ans[m][n] = t; }
  //     }
  //     t++;
  //     return;
  //   }

  //   if (v == -3) return;

  //   if (v & FLAG) {
  //     int m = v ^ FLAG;
  //     self(self, i, m, k, l);
  //     self(self, i, j - m, k, l + m);
  //   } else {
  //     int m = v;
  //     self(self, m, j, k, l);
  //     self(self, i - m, j, k + m, l);
  //   }
  // };
  // dfs(dfs, N, M, 0, 0);

  // map<int, char> labels;
  // t = 0;
  // auto to_label = [&](int t) -> char {
  //   return t < 26 ? 'A' + t : 'a' + t - 26;
  // };

  // rep(i, 0, N) {
  //   rep(j, 0, M) {
  //     int v = ans[i][j];
  //     if (v == -1) {
  //       cout << '#';
  //     } else {
  //       if (!labels.contains(v)) {
  //         labels[v] = to_label(t);
  //         t++;
  //       }
  //       cout << labels[v];
  //     }
  //   }
  //   cout << '\n';
  // }
}