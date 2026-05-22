#ifndef L
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

  auto to_string = [&](int x, int b) -> string {
    string rv = "";
    for (; x; x /= b) {
      rv += (char) ('0' + x % b);
    }
    reverse(all(rv));
    return rv;
  };

  map<string, vi> S;
  rep(i, 0, 3125) {
    auto s = to_string(i, 5);
    sort(all(s));
    S[s].pb(i);
  }
  vc<pair<int, string>> S2;
  for (auto [k, v] : S) {
    set<int> T;
    rep(i, 0, sz(v)) {
      rep(j, i + 1, sz(v)) { T.insert(v[j] - v[i]); }
    }
    S2.eb(sz(T), k);
  }
  sort(S2.rbegin(), S2.rend());
  rep(i, 0, 10) {
    auto [t, k] = S2[i];
    cerr << t << ' ' << k << '\n';
  }
}
