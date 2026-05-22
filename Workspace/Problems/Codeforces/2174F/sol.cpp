#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint1000000007;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<int> C(N);
    for (auto &e : C) {
      cin >> e;
      e--;
    }

    vector<int> mask(M);
    for (auto &e : mask) cin >> e;

    if (N < 2) {
      cout << (count(mask.begin(), mask.end(), 0) == M ? 1 : 0) << '\n';
      continue;
    }

    vector<int> counts(M, 0);
    for (auto e : C) {
      counts[e]++;
    }

    // https://en.wikipedia.org/wiki/Pr%C3%BCfer_sequence

    vector dp1(2, vector<mint>(N + 1, 0));
    dp1[0][N] = 1;
    for (int i = 0; i < N - 2; i++) {
      for (int j = 0; j <= N; j++) {
        if (j + 1 <= N) {
          dp1[(i + 1) % 2][j + 1] += dp1[i % 2][j] * (N - j);
        }
        if (j - 1 >= 0) {
          dp1[(i + 1) % 2][j - 1] += dp1[i % 2][j] * j;
        }
        dp1[i % 2][j] = 0;
      }
    }
    for (int i = 0; i <= N; i++) {
      dp1[(N - 2) % 2][i] /= binom<mint>(N, i);
    }

    vector<vector<int>> check(N + 1);
    int j = 0;
    for (int i = 0; i < M; i++) {
      j += counts[i];
      check[j].push_back(mask[i]);
    }

    vector dp2(2, vector(N + 1, vector<mint>(2, 0)));
    dp2[0][0][0] = 1;
    for (int i = 0; i <= N; i++) {
      for (int j = 0; j <= i; j++) {
        for (auto e : check[i]) {
          dp2[i % 2][j][0] = dp2[i % 2][j][e];
          dp2[i % 2][j][1] = 0;
        }

        if (i + 1 <= N) {
          for (int k = 0; k < 2; k++) {
            dp2[(i + 1) % 2][j + 1][(k + 1) % 2] += dp2[i % 2][j][k];
            dp2[(i + 1) % 2][j][k] += dp2[i % 2][j][k];
            dp2[i % 2][j][k] = 0;
          }
        }
      }
    }

    mint ans = 0;
    for (int i = 0; i <= N; i++) {
      ans += dp1[(N - 2) % 2][i] * dp2[N % 2][i][0];
    }
    cout << ans.val() << '\n';
  }
}
