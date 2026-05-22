#include <bits/stdc++.h>

#include <utility>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int K;
  cin >> K;

  string S;
  cin >> S;

  int N = S.size();

  if (K == 2) {
    auto chmin = [&](tuple<int, int, int, int> &a,
                     tuple<int, int, int, int> b) -> void { a = min(a, b); };
    vector dp(N + 1, vector(2, vector<tuple<int, int, int, int>>(
                                   2, {INF, -1, -1, -1})));
    dp[0][0][0] = {0, -1, -1, -1};
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
          for (int l = 0; l < 2; l++) {
            int k_ = j == l ? k + 1 : 1;
            if (k_ < 2) {
              auto [sum, pj, pk, c] = dp[i][j][k];
              chmin(dp[i + 1][l][k_], {sum + (l + '0' != S[i]), j, k, l});
            }
          }
        }
      }
    }
    tuple<int, int, int> ans = {INF, -1, -1};
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        auto [sum, pj, pk, c] = dp[N][i][j];
        ans = min(ans, {sum, i, j});
      }
    }
    auto [sum, j, k] = ans;
    cout << sum << ' ';
    string s = "";
    for (int i = N; i > 0; i--) {
      auto [sum, pj, pk, c] = dp[i][j][k];
      s += c + '0';
      tie(j, k) = make_pair(pj, pk);
    }
    reverse(s.begin(), s.end());
    cout << s;
    exit(0);
  }

  char c;
  int n = 0, ans = 0;
  for (int i = 0; i < N; i++) {
    if (S[i] != c) {
      c = S[i];
      n = 0;
    }
    n++;
    if (n >= K) {
      ans++;
      if (i + 1 < N and S[i + 1] == c) {
        S[i] = c ^ 1;
      } else {
        S[i - 1] = c ^ 1;
      }
      c = S[i];
      n = 1;
    }
  }
  cout << ans << ' ' << S;
}