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

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  char cards[] = "A23456789TJQK";

  vc<int> hand(N);
  for (auto &e : hand) {
    char c;
    cin >> c;
    e = find(all(cards), c) - begin(cards);
  }
  sort(all(hand));

  auto value = [&](int i) -> int { return min(i + 1, 10ll); };

  vi counts(13, 0);
  for (auto e : hand) {
    counts[e]++;
  }

  int ans = 0;

  {
    rep(i, 0, 13) { ans += counts[i] * (counts[i] - 1); }
  }

  {
    vc dp(N + 1, vi(15 + 1, 0));
    dp[0][0] = 1;
    rep(i, 0, N) {
      rep(j, 0, 15 + 1) {
        int v = value(hand[i]);
        if (j + v <= 15) {
          dp[i + 1][j + v] += dp[i][j];
        }
        dp[i + 1][j] += dp[i][j];
      }
    }
    ans += 2 * dp[N][15];
  }

  {
    rep(i, 0, 13) {
      if (i - 1 >= 0 and counts[i - 1] > 0) continue;
      rep(j, i + 2, 13) {
        if (j + 1 < 13 and counts[j + 1] > 0) continue;
        int count = 1;
        rep(k, i, j + 1) { count *= counts[k]; }
        ans += (j + 1 - i) * count;
      }
    }
  }

  cout << ans;
}