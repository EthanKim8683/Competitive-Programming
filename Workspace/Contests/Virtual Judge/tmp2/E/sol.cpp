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

  // lexicographically smallest permutation
  //
  // merge each group

  int N;
  cin >> N;

  vi P(N);
  for (auto &e : P) cin >> e;

  vc<string> A(N);
  for (auto &e : A) cin >> e;

  dsu d(N);
  rep(i, 0, N) {
    rep(j, 0, N) {
      if (A[i][j] == '1') {
        d.merge(i, j);
      }
    }
  }

  vc<vi> by_leader(N);
  rep(i, 0, N) { by_leader[d.leader(i)].pb(P[i]); }
  rep(i, 0, N) { sort(all(by_leader[i])); }

  vi counter(N, 0), ans(N);
  rep(i, 0, N) {
    int j = d.leader(i);
    ans[i] = by_leader[j][counter[j]];
    counter[j]++;
  }
  for (auto e : ans) {
    cout << e << ' ';
  }
  cout << '\n';
}
