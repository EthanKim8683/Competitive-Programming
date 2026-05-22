#pragma GCC optimize("trapv")
#include <bits/stdc++.h>
using namespace std;

#define int long long
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

const int MAXC = 1000;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // weird knapsack
  // maybe bitset?

  int C, N;
  cin >> C >> N;

  vc<int> A(N);
  for (auto &e : A) cin >> e;

  vc dp(N + 1, vc<bitset<MAXC + 1>>(C + 1));
  dp[0][0][0] = true;
  rep(i, 0, N) {
    rep(j, 0, C + 1) {
      if (j + A[i] <= C) {
        dp[i + 1][j + A[i]] |= dp[i][j];
      }
      dp[i + 1][j] |= dp[i][j] << A[i];
      dp[i + 1][j] |= dp[i][j];
    }
  }
  tuple<int, int, int, int> best = {0, 0, 0, 0};
  rep(i, 0, C + 1) {
    rep(j, 0, i + 1) {
      if (!dp[N][i][j]) continue;
      best = max(best, {i + j, j - i, i, j});
    }
  }
  auto [sum, diff, a, b] = best;
  cout << a << ' ' << b;
}