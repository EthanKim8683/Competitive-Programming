#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    i64 M;
    cin >> N >> M;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<int> B(N);
    for (auto &e : B) cin >> e;

    int K = 1;
    for (auto e : A) {
      K = lcm(K, e);
    }

    auto ok = [&](int i, int j) -> bool { return i % A[j % N] != B[j % N]; };

    auto chmin = [&](i64 &a, i64 b) -> void { a = min(a, b); };

    vector dp1(N, vector(K + 1, vector<i64>(N, INF)));
    for (int i = 0; i < N; i++) {
      dp1[i][0][i] = 0;
      for (int j = 0; j <= K; j++) {
        for (int k = 0; k < 2 * N; k++) {
          if (ok(j, k)) {
            chmin(dp1[i][j][(k + 1) % N], dp1[i][j][k % N] + 1);
          }
          if (j + 1 <= K and ok(j + 1, k)) {
            chmin(dp1[i][j + 1][(k + 1) % N], dp1[i][j][k % N] + 1);
          }
        }
      }
    }

    auto prod = [&](vector<vector<i64>> A,
                    vector<vector<i64>> B) -> vector<vector<i64>> {
      vector rv(N, vector<i64>(N, INF));
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          for (int k = 0; k < N; k++) {
            chmin(rv[i][j], A[i][k] + B[k][j]);
          }
        }
      }
      return rv;
    };

    auto id = [&]() -> vector<vector<i64>> {
      vector rv(N, vector<i64>(N, INF));
      for (i64 i = 0; i < N; i++) {
        rv[i][i] = 0;
      }
      return rv;
    };

    auto pow = [&](vector<vector<i64>> X, i64 y) -> vector<vector<i64>> {
      auto rv = id();
      for (; y; y >>= 1, X = prod(X, X)) {
        if (y & 1) {
          rv = prod(rv, X);
        }
      }
      return rv;
    };

    vector X(N, vector<i64>(N));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        X[i][j] = dp1[i][K][j];
      }
    }
    auto dp2 = pow(X, M / K);

    i64 ans = INF;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        chmin(ans, dp2[0][i] + dp1[i][M % K][j]);
      }
    }
    cout << (ans == INF ? -1 : ans) << '\n';
  }
}
