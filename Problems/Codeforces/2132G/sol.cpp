#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using i128 = __int128;

const int MAXNM = 1e6;
const int BASE = 6969;
const i64 MOD = (1ll << 61) - 1;
const int INF = 1e9;

int main(int argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);

  // start: 8:14
  // thinking done: 8:20
  // target impl time: 25 min
  // initial impl done: 8:59

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  vector<i64> pows(MAXNM + 1);
  pows[0] = 1;
  for (int i = 1; i <= MAXNM; i++) {
    pows[i] = (i128) pows[i - 1] * BASE % MOD;
  }

  auto mod_pow = [&](i64 x, i64 y) -> i64 {
    i64 rv = 1;
    for (x %= MOD; y; y >>= 1, x = (i128) x * x % MOD) {
      if (y & 1) {
        rv = (i128) rv * x % MOD;
      }
    }
    return rv;
  };

  auto mod_inv = [&](i64 x) -> i64 { return mod_pow(x, MOD - 2); };

  i64 inv_base = mod_inv(BASE);

  vector<i64> inv_pows(MAXNM + 1);
  inv_pows[0] = 1;
  for (int i = 1; i <= MAXNM; i++) {
    inv_pows[i] = (i128) inv_pows[i - 1] * inv_base % MOD;
  }

  int T;
  if (argc > 1) {
    T = 1e6 / (5 * 5);
  } else {
    cin >> T;
  }

  while (T--) {
    int N, M;
    if (argc > 1) {
      N = 5;
      M = 5;
    } else {
      cin >> N >> M;
    }

    vector<string> table(N);
    if (argc > 1) {
      for (auto &r : table) {
        r.resize(M);
        for (auto &e : r) {
          e = (char) ('a' + rng() % 26);
        }
      }
    } else {
      for (auto &e : table) {
        cin >> e;
      }
    }

    auto make_ps = [&](vector<string> table) -> vector<vector<i64>> {
      int n = table.size(), m = table[0].size();
      vector ps(n + 1, vector<i64>(m + 1, 0));
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          (ps[i + 1][j + 1] += (i128) table[i][j] * pows[i * m + j] % MOD) %=
              MOD;
        }
      }
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
          (ps[i][j] += ps[i - 1][j] + ps[i][j - 1] + MOD - ps[i - 1][j - 1]) %=
              MOD;
        }
      }
      return ps;
    };
    auto query = [&](vector<vector<i64>> &ps, int l1, int r1, int l2,
                     int r2) -> i64 {
      int m = ps[0].size() - 1;
      return (i128) (ps[r1][r2] + MOD - ps[l1][r2] + MOD - ps[r1][l2] +
                     ps[l1][l2]) *
             inv_pows[l1 * m + l2] % MOD;
    };

    auto rotate180 = [&](vector<string> table) -> vector<string> {
      int n = table.size(), m = table[0].size();
      vector<string> rv(n);
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          rv[i] += table[n - 1 - i][m - 1 - j];
        }
      }
      return rv;
    };

    auto ps1 = make_ps(table), ps2 = make_ps(rotate180(table));
    int ans = INF;
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
        for (auto k : (int[]) {0, N - i}) {
          for (auto l : (int[]) {0, M - j}) {
            if (query(ps1, k, k + i, l, l + j) ==
                query(ps2, N - (k + i), N - k, M - (l + j), M - l)) {
              ans = min(ans, 3 * N * M - 2 * i * M - 2 * N * j + i * j);
            }
          }
        }
      }
    }
    if (argc > 1) {
    } else {
      cout << ans << '\n';
    }
  }
}
