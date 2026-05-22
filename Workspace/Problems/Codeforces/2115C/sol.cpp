#include <bits/stdc++.h>

using namespace std;

const int MAXH = 400;
const double INF = 1. / 0;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // 4000 * 400 * 100

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    double P;
    cin >> N >> M >> P;
    P /= 100;

    vector<int> H(N);
    for (auto &e : H) cin >> e;

    vector dp1(M + 1, vector<double>(MAXH * N + 1, -INF));
    for (int i = 0; i <= MAXH * N; i++) {
      if (i == N) {
        dp1[M][i] = 1;
      } else {
        dp1[M][i] = 0;
      }
    }
    for (int i = M - 1; i >= 0; i--) {
      for (int j = 0; j <= MAXH * N; j++) {
        double p1 = dp1[i + 1][j], p2 = dp1[i + 1][j];
        if (j - N >= 0) {
          p1 = max(p1, dp1[i + 1][j - N]);
        }
        if (j - 1 >= 0) {
          p2 = max(p2, dp1[i + 1][j - 1]);
        }
        dp1[i][j] = P * p1 + (1 - P) * p2;
      }
    }

    int h = *min_element(H.begin(), H.end()),
        d = accumulate(H.begin(), H.end(), 0) - N * h;
    double ans = 0;
    vector dp2(2, vector<double>(d + 1, 0));
    dp2[0][0] = 1;
    for (int i = 0; i <= M; i++) {
      for (int j = 0; j <= d; j++) {
        if (j <= i and d - j < N) {
          ans += dp2[i % 2][j] * dp1[i][max(h - (i - j), 1) * N + d - j];
        } else {
          if (i + 1 <= M) {
            dp2[(i + 1) % 2][j] += dp2[i % 2][j] * P;

            if (j + 1 <= d) {
              dp2[(i + 1) % 2][j + 1] += dp2[i % 2][j] * (1 - P);
            }
          }
        }
        dp2[i % 2][j] = 0;
      }
    }
    cout << setprecision(6) << fixed << ans << '\n';
  }
}
