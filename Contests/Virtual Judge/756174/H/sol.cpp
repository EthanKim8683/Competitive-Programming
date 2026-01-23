#include <bits/stdc++.h>
using namespace std;

#define int long long
#define float long double
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef vector<int> vi;

const int BASE = 6969;
const int MOD = (1ll << 31) - 1;
const int INF = 1e9;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // dp

  string S;
  cin >> S;

  int N = S.size();

  vi pow(N + 1);
  pow[0] = 1;
  rep(i, 1, N + 1) { pow[i] = pow[i - 1] * BASE % MOD; }

  vi ph(N + 1, 0);
  rep(i, 0, N) { ph[i + 1] = (ph[i] * BASE + S[i]) % MOD; }

  auto hash = [&](int l, int r) -> int {
    return ((ph[r] - ph[l] * pow[r - l]) % MOD + MOD) % MOD;
  };

  auto chmin = [&](piii &a, piii b) -> void { a = min(a, b); };

  auto size = [&](int x) -> int {
    int rv = 0;
    while (x) {
      rv++;
      x /= 10;
    }
    return rv;
  };

  vc dp(N + 1, vc<piii>(N + 1, {INF, -1, -1}));
  auto solve = [&](auto self, int l, int r) -> piii {
    if (dp[l][r] != piii{INF, -1, -1}) return dp[l][r];
    if (r - l <= 1) return {r - l, -1, -1};

    rep(i, 1, r - l + 1) {
      rep(j, 1, min((r - l) / i + 1, 9ll + 1)) {
        if (hash(l + i * (j - 1), l + i * j) != hash(l, l + i)) break;
        auto [len1, _i1, _j1] = self(self, l, l + i);
        auto [len2, _i2, _j2] = self(self, l + i * j, r);
        if (j == 1) {
          chmin(dp[l][r], {len1 + len2, i, j});
        } else {
          chmin(dp[l][r], {size(j) + 1 + len1 + 1 + len2, i, j});
        }
      }
    }
    return dp[l][r];
  };
  solve(solve, 0, N);

  auto build = [&](auto self, int l, int r) -> string {
    if (r - l <= 1) return S.substr(l, r - l);

    auto [len, i, j] = dp[l][r];
    auto str1 = self(self, l, l + i);
    auto str2 = self(self, l + i * j, r);
    if (j == 1) {
      return str1 + str2;
    } else {
      return to_string(j) + "(" + str1 + ")" + str2;
    }
  };
  cout << build(build, 0, N);
}