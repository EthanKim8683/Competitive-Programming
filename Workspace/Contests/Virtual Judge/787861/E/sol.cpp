#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string S;
  cin >> S;

  int N = S.size();

  vector<mint> pows(N + 1);
  pows[0] = 1;
  for (int i = 1; i <= N; i++) {
    pows[i] = pows[i - 1] * 26;
  }

  auto is_equal = [&](char a, char b) -> bool {
    return a == '?' or b == '?' or a == b;
  };

  vector<mint> dp(N + 1, 0);
  dp[0] = 1;
  for (int i = N - 1; i >= 1; i--) {
    vector<int> ps(N + 1, 0);
    int k = -1;
    for (int j = N - 1 - i; j >= 0; j--) {
      if (is_equal(S[j], S[j + i])) {
        if (k == -1) {
          k = j + 1;
        }
        ps[j] = ps[j + 1];
        if (S[j] == '?' and S[j + i] == '?') {
          ps[j] += 1;
        }
        if (j < N - (j + i) and k >= N - (j + i)) {
          dp[N - (j + i)] += dp[j] * pows[ps[j] - ps[N - (j + i)]];
        }
      } else {
        k = -1;
      }
    }
  }
  vector<int> ps(N + 1, 0);
  for (int i = 0; i < N; i++) {
    ps[i + 1] = ps[i];
    if (S[i] == '?') {
      ps[i + 1] += 1;
    }
  }
  mint ans = 0;
  for (int i = 0; i <= N / 2; i++) {
    ans += dp[i] * pows[ps[N - i] - ps[i]];
  }
  cout << ans.val() << '\n';
}
