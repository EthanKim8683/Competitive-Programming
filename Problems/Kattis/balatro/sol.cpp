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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, K;
  cin >> N >> K;

  vc<pair<char, int>> cards(N);
  for (auto &[s, v] : cards) {
    cin >> s >> v;
  }

  vi indices;
  rep(i, 0, N) {
    auto [s, v] = cards[i];
    if (s != 'm') continue;
    indices.pb(i);
  }

  auto from_ps = [&](vi ps) -> vi {
    vi rv(sz(ps) - 1);
    rep(i, 0, sz(ps) - 1) { rv[i] = ps[i + 1] - ps[i]; }
    return rv;
  };

  auto to_ps = [&](vi v) -> vi {
    vi rv(sz(v) + 1);
    rv[0] = 0;
    rep(i, 0, sz(v)) { rv[i + 1] = rv[i] + v[i]; }
    return rv;
  };

  vc<vi> dp;
  dp.push_back({0});
  int l = 0;
  for (auto r : indices) {
    for (auto &ps : dp) {
      auto v = from_ps(ps);
      rep(i, l, r) { v.pb(cards[i].sd); }
      sort(v.rbegin(), v.rend());
      ps = to_ps(v);
    }

    for (int i = sz(dp) - 1; i >= 0; i--) {
      auto ps = dp[i];
      for (auto &e : ps) {
        e *= cards[r].sd;
      }

      if (i + 1 < sz(dp)) {
        rep(j, 0, sz(ps)) { chmax(dp[i + 1][j], ps[j]); }
      } else {
        dp.pb(ps);
      }
    }

    for (auto r : dp) {
      for (auto e : r) {
        cerr << e << ' ';
      }
      cerr << '\n';
    }
    cerr << '\n';

    l = r + 1;
  }
  for (auto &ps : dp) {
    auto v = from_ps(ps);
    rep(i, l, N) { v.pb(cards[i].sd); }
    sort(v.rbegin(), v.rend());
    ps = to_ps(v);
  }

  for (auto r : dp) {
    for (auto e : r) {
      cerr << e << ' ';
    }
    cerr << '\n';
  }

  int ans = 0;
  rep(i, 1, N + 1) {
    rep(j, 0, min(i + 1, min(K + 1, sz(dp)))) {
      chmax(ans, dp[j][min(i - j, sz(dp[j]) - 1)]);
    }
    cout << ans << '\n';
  }
}
