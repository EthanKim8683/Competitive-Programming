#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int LOGA = 29;
const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<i64> A(N - 1);
    for (auto &e : A) cin >> e;

    vector<i64> B(N);
    for (auto &e : B) cin >> e;

    vector<i64> C(N);
    C[0] = A[0];
    C[N - 1] = A[N - 2];
    for (int i = 0; i + 1 < N - 1; i++) {
      C[i + 1] = A[i] | A[i + 1];
    }

    auto get_mask = [&](int i, int j) -> i64 {
      if (j == 0) return B[i];
      i64 rv = 0;
      rv |= B[i] & ~((1ll << (j - 1)) - 1);
      rv |= C[i] & ((1ll << (j - 1)) - 1);
      rv |= 1ll << (j - 1);
      return rv;
    };

    auto chmin = [&](i64 &a, i64 b) -> void { a = min(a, b); };

    vector dp(N, vector<i64>(LOGA + 3, INF));
    for (int i = 0; i <= LOGA + 2; i++) {
      if (get_mask(0, i) < B[0]) continue;
      dp[0][i] = get_mask(0, i) - B[0];
    }
    for (int i = 0; i + 1 < N; i++) {
      for (int j = 0; j <= LOGA + 2; j++) {
        for (int k = 0; k <= LOGA + 2; k++) {
          if (get_mask(i + 1, k) < B[i + 1]) continue;
          if ((get_mask(i, j) & get_mask(i + 1, k)) != A[i]) continue;
          chmin(dp[i + 1][k], dp[i][j] + get_mask(i + 1, k) - B[i + 1]);
        }
      }
    }
    i64 ans = *min_element(dp[N - 1].begin(), dp[N - 1].end());
    cout << (ans == INF ? -1 : ans) << '\n';
  }
}
