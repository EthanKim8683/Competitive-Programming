#pragma GCC optimize("Ofast,unroll-loops")
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

const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int R, C;
  cin >> R >> C;

  vc<string> room(R);
  for (auto &e : room) cin >> e;

  if (C > R) {
    swap(R, C);

    auto room0 = room;

    room = vc(R, string(C, ' '));
    rep(i, 0, R) {
      rep(j, 0, C) { room[i][j] = room0[j][i]; }
    }
  }

  auto is_valid = [&](int mask) -> bool {
    rep(i, 0, C - 1) {
      if ((mask >> i & 1) and (mask >> (i + 1) & 1)) return false;
    }
    return true;
  };

  auto is_satisfactory = [&](int i, int mask) -> bool {
    rep(j, 0, C) {
      if (room[i][j] == '2' and (~mask >> j & 1)) return false;
      if (room[i][j] == '0' and (mask >> j & 1)) return false;
    }
    return true;
  };

  auto combine = [&](pii &a, pii b) -> void {
    if (b.fs > a.fs) {
      a = b;
    } else if (b.fs == a.fs) {
      (a.sd += b.sd) %= MOD;
    }
  };

  vc dp(R, vc<pii>(1 << C, {0, 0}));
  rep(i, 0, 1 << C) { dp[0][i] = {0, 1}; }
  rep(i, 0, R) {
    rep(j, 0, 1 << C) { dp[i][j].fs += __builtin_popcount(j); }

    rep(j, 0, 1 << C) {
      if (is_valid(j) and is_satisfactory(i, j)) continue;
      dp[i][j] = {0, 0};
    }

    if (i + 1 < R) {
      vc<pii> dp2(1 << C, {0, 0});
      rep(j, 0, 1 << C) { combine(dp2[j ^ ((1 << C) - 1)], dp[i][j]); }

      rep(j, 0, C) {
        rep(k, 0, 1 << C) {
          if (k >> j & 1) continue;
          combine(dp2[k], dp2[k ^ 1 << j]);
        }
      }

      dp[i + 1] = dp2;
    }
  }

  pii ans = {0, 0};
  for (auto e : dp[R - 1]) {
    combine(ans, e);
  }

  auto [s, w] = ans;
  for (auto r : room) {
    for (auto e : r) {
      if (e != '2') continue;
      s--;
    }
  }

  cout << s << ' ' << w;
}
