#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/dsu.hpp"
using namespace atcoder;

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

  // if (A[i]^A[j])<4, (A[j]^A[k])<4, (A[i]^A[k])<4
  //
  // dsu and sort each component

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    dsu d(N);
    map<int, int> leaders;
    rep(i, 0, N) {
      if (!leaders.contains(A[i])) {
        leaders.insert({A[i], i});
      } else {
        d.merge(leaders[A[i]], i);
      }
    }
    for (auto [k, leader] : leaders) {
      rep(i, 0, 4) {
        if (!leaders.contains(k ^ i)) continue;
        d.merge(leader, leaders[k ^ i]);
      }
    }

    vc<vi> by_leader(N);
    rep(i, 0, N) { by_leader[d.leader(i)].pb(A[i]); }
    rep(i, 0, N) { sort(all(by_leader[i])); }
    vi index(N, 0), ans(N);
    rep(i, 0, N) {
      int r = d.leader(i);
      ans[i] = by_leader[r][index[r]];
      index[r]++;
    }
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
