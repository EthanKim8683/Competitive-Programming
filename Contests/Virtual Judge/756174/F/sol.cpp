#include <bits/stdc++.h>

#include <iomanip>
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
typedef vector<int> vi;
typedef pair<float, float> pff;

const float INF = 1 / 0.;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // play until cannot make any sum
  // this is probably dp? bitwise
  // ah! but it's EV
  // so i choose which numbers to remove on this round to min/maximize EV
  // still dp probably

  string S;
  int A, B;
  cin >> S >> A >> B;

  int mask0 = 0;
  for (auto e : S) {
    mask0 |= 1 << (e - '1');
  }

  vc<float> P(12 + 1, 0);
  rep(i, 1, 6 + 1) {
    rep(j, 1, 6 + 1) { P[i + j] += 1.L / (6 * 6); }
  }

  auto score = [&](int mask) -> float {
    int rv = 0;
    rep(j, 0, 9) {
      if (~mask >> j & 1) continue;
      rv = rv * 10 + j + 1;
    }
    return rv;
  };

  vc<pff> dp(1 << 9, {-1, -1});
  auto dfs = [&](auto self, int mask) -> pff {
    if (dp[mask].fs >= 0) return dp[mask];

    auto &[best, worst] = dp[mask];
    best = 0;
    worst = 0;
    rep(i, 1, 12 + 1) {
      bool found = false;
      float besti = -INF, worsti = INF;
      rep(j, 0, 1 << 9) {
        if ((mask & j) != j) continue;

        int sum = 0;
        rep(k, 0, 9) {
          if (~(mask ^ j) >> k & 1) continue;
          sum += k + 1;
        }
        if (sum != i) continue;

        found = true;
        auto [bestj, worstj] = self(self, j);
        besti = max(besti, bestj);
        worsti = min(worsti, worstj);
      }

      if (!found) {
        auto scorei = score(mask);
        besti = scorei;
        worsti = scorei;
      }

      best += besti * P[i];
      worst += worsti * P[i];
    }
    return dp[mask];
  };
  bool found = false;
  pair<float, int> best = {-INF, -1}, worst = {INF, -1};
  rep(i, 0, 1 << 9) {
    if ((mask0 & i) != i) continue;

    int sum = 0;
    rep(j, 0, 9) {
      if (~(mask0 ^ i) >> j & 1) continue;
      sum += j + 1;
    }
    if (sum != A + B) continue;

    found = true;
    auto [besti, worsti] = dfs(dfs, i);
    best = max(best, {besti, i});
    worst = min(worst, {worsti, i});
  }
  if (!found) {
    int score0 = score(mask0);
    best = {score0, mask0};
    worst = {score0, mask0};
  }

  auto to_string = [&](int mask) -> string {
    string rv = "";
    rep(i, 0, 9) {
      if (~(mask0 ^ mask) >> i & 1) continue;
      rv += (char) i + '1';
    }
    if (rv.empty()) return "-1";
    return rv;
  };

  auto [best_score, best_mask] = best;
  auto [worst_score, worst_mask] = worst;

  cout << setprecision(5) << fixed;
  cout << to_string(worst_mask) << ' ' << worst_score << '\n';
  cout << to_string(best_mask) << ' ' << best_score << '\n';
}