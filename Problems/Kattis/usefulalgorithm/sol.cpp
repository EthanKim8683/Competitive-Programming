#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
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
typedef vc<int> vi;

const int MOD = 1e9 + 7;
const int LOGN = 32;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    auto mod_pow = [&](int x, int y) -> int {
      int rv = 1;
      for (x %= MOD; y; y >>= 1, (x *= x) %= MOD) {
        if (y & 1) {
          (rv *= x) %= MOD;
        }
      }
      return rv;
    };

    auto mod_inv = [&](int x) -> int { return mod_pow(x, MOD - 2); };

    vi memo1 = {1}, memo2 = {1}, memo3 = {1};
    rep(i, 1, LOGN) {
      memo1.pb(memo1.back() * (K - 1 + 1 - i) % MOD);
      memo2.pb(memo2.back() * (N - K + 1 - i) % MOD);
      memo3.pb(memo3.back() * mod_inv(N + 1 - i) % MOD);
    }

    auto encode = [&](int n, int lt, int ge) -> int {
      return n * LOGN * LOGN + lt * LOGN + ge;
    };

    auto decode = [&](int x) -> tuple<int, int, int> {
      return {x / (LOGN * LOGN), x / LOGN % LOGN, x % LOGN};
    };

    vc<vc<tuple<int, int, int>>> dp(LOGN);
    dp[0].eb(N, 0, 1);
    int ans = 0;
    rep(i, 0, LOGN) {
      vc<tuple<int, int, int>> dp2;
      sort(all(dp[i]));
      for (auto [n, lt, count] : dp[i]) {
        if (dp2.empty()) {
          dp2.eb(n, lt, count);
        } else {
          auto &[n2, lt2, count2] = dp2.back();
          if (pair{n, lt} == pair{n2, lt2}) {
            count2 += count;
          } else {
            dp2.eb(n, lt, count);
          }
        }
      }

      for (auto [n, lt, count] : dp2) {
        int ge = i - lt;
        if (n == 1) {
          int contribution = count;
          if (ge >= 1) {
            (contribution *= memo1[lt]) %= MOD;
            (contribution *= memo2[ge - 1]) %= MOD;
            (contribution *= memo3[lt + ge]) %= MOD;
          } else {
            (contribution *= memo1[lt]) %= MOD;
            (contribution *= memo3[lt + 1]) %= MOD;
          }
          (ans += contribution) %= MOD;
        } else {
          dp[i + 1].eb((n + 1) / 2, lt, count);
          dp[i + 1].eb(n / 2, lt + 1, count);
        }
      }
    }
    cout << ans << '\n';
  }
}
