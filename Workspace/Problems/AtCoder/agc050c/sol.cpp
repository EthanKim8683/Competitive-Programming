#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string S;
  cin >> S;
  reverse(S.begin(), S.end());

  int N = S.size();

  int Q = 0;
  for (auto e : S) {
    Q += e == '?';
  }

  vector<int> ps(N + 1);
  ps[0] = 0;
  for (int i = 0; i < N; i++) {
    ps[i + 1] = ps[i] + (S[i] == 'B');
  }

  vector<int> gaps(22);
  gaps[0] = 2;
  for (int i = 0; i + 1 < 22; i++) {
    gaps[i + 1] = gaps[i] * 2 - 1;
  }

  vector<mint> dp(22, 0);
  vector start(N, vector<mint>(22, 0));
  dp[0] = 1;
  mint ans = 0;
  if (ps[N] - ps[0] == 0) {
    ans += 1;
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 22; j++) {
      dp[j] += start[i][j];
    }

    if (S[i] != 'S') {
      for (int j = 0; j + 1 < 22; j++) {
        int i2 = i + gaps[j];
        if (i2 < N and ps[i2] - ps[i + 1] == 0) {
          start[i2][j + 1] += dp[j];
        }
      }
      if (ps[N] - ps[i + 1] == 0) {
        for (int j = 0; j < 22; j++) {
          ans += dp[j];
        }
      }
    }

    if (S[i] == 'B') {
      fill(dp.begin(), dp.end(), 0);
    }
  }
  ans = mint(2).pow(Q) - ans;
  cout << ans.val();
}
