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

const int MAXH = 8;
const int MAXW = 8;
const int MAXN = MAXH * MAXW;
const int LOGP = 6;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  vc dp(LOGP + 1, vc(MAXN + 1, vc(MAXN + 1, vc<char>(2, false))));
  rep(i, 1, LOGP + 1) {
    int p = 1 << i;
    rep(j, 0, p) {
      rep(k, 0, j + 1) { dp[i][j][k][(~j & k) != 0] = true; }
    }
    rep(j, 0, MAXN + 1 - p) {
      rep(k, 0, MAXN + 1) {
        rep(l, 0, 2) {
          rep(m, 0, min(MAXN + 1 - k, p + 1)) {
            dp[i][j + p][k + m][l or (~p & m) != 0] |= dp[i][j][k][l];
          }
        }
      }
    }
  }

  set<int> N;
  rep(i, 1, MAXH + 1) {
    rep(j, 1, MAXW + 1) { N.insert(i * j); }
  }
  vc P(MAXN + 1, vi(MAXN, -1));
  for (auto e : N) {
    rep(i, 1, e) {
      if ((~e & i) == 0) continue;
      rep(j, 1, LOGP + 1) {
        if (dp[j][e][i][0]) continue;
        P[e][i] = 1 << j;
        break;
      }
      assert(P[e][i] != -1);
      assert(P[e][i] <= e);
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int H, W, K;
    cin >> H >> W >> K;

    vc<string> room(H);
    for (auto &e : room) cin >> e;

    string s = "";
    for (auto e : room) {
      s += e;
    }

    pii nil = {-1, -1};
    auto dfs = [&](auto self, string s) -> pii {
      if (__builtin_popcount(sz(s)) == 1) {
        if (sz(s) == 1) return nil;

        auto it = s.begin() + sz(s) / 2;
        if (count(s.begin(), it, '#') == count(it, s.end(), '#'))
          return self(self, {s.begin(), it});

        for (int l = 0, r = sz(s) - 1; l < r; l++, r--) {
          if (s[l] == '#' and s[r] == '.') return {l, r};
          if (s[l] == '.' and s[r] == '#') return {r, l};
        }
        assert(false);
      }

      int p = P[sz(s)][count(all(s), '#')];
      if (p == -1) return nil;

      for (int i = 0; i < sz(s); i += p) {
        auto t = self(self, s.substr(i, p));
        if (t != nil) return {i + t.fs, i + t.sd};
      }
      assert(false);
    };
    auto ans = dfs(dfs, s);
    if (ans == nil) {
      cout << "risky\n";
    } else {
      auto [a, b] = ans;
      cout << a / W + 1 << ' ' << a % W + 1 << '\n';
      cout << b / W + 1 << ' ' << b % W + 1 << '\n';
    }
  }
}
