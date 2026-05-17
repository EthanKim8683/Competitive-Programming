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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string S;
  cin >> S;

  vc<char> cc;
  for (auto e : S) {
    cc.pb(e);
  }
  sort(all(cc));
  cc.erase(unique(all(cc)), cc.end());
  auto compress = [&](char c) -> int {
    return lower_bound(all(cc), c) - cc.begin();
  };
  for (auto &e : S) {
    e = compress(e);
  }

  int M = sz(cc);

  vc weights(M, vi(M, 0));
  rep(i, 0, sz(S) - 1) {
    int a = S[i], b = S[i + 1];
    weights[a][b] += 1;
    if (b != a) {
      weights[b][a] += 1;
    }
  }

  vi dp(1 << M, INF);
  dp[0] = 0;
  rep(i, 0, 1 << M) {
    int j = __builtin_popcount(i);
    rep(k, 0, M) {
      if (i >> k & 1) continue;
      int delta = 0;
      rep(l, 0, M) {
        if (i >> l & 1) {
          delta += weights[l][k];
        } else if (l != k) {
          delta -= weights[k][l];
        }
      }
      chmin(dp[i | 1 << k], dp[i] + delta * j);
    }
  }
  cout << dp[(1 << M) - 1] << '\n';
}
