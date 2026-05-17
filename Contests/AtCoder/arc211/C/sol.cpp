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

  // we never want to remove multiple groups of trees at a time
  //
  // every group must be removed optimally
  //
  // count all operations s.t. no operation before it reveals better R for it to
  // use
  //
  // R R R R R R R R R
  //   #   #   #   #
  // R R R R R R R (add two R's, merge three R's)
  //   #   #   #
  //
  // each R must contribute at least once
  //
  // if we use the max R every time does that guarantee optimal answer? yes
  // because it contributes max(R) * (N - 2) more than the base
  //
  // if max R is available, have to use it

  int N;
  cin >> N;

  string S;
  cin >> S;

  vi R(N);
  for (auto &e : R) cin >> e;

  vc<pii> ranges;
  for (int i = 0, j = 0; i < N; ranges.eb(i, j), i = j) {
    for (; j < N and S[j] == S[i]; j++);
  }

  vc<char> S2;
  vc<pii> R2;
  for (auto [l, r] : ranges) {
    int rmax = 0, rcount = 0;
    rep(i, l, r) {
      if (R[i] > rmax) {
        rmax = R[i];
        rcount = 0;
      }
      if (R[i] == rmax) {
        rcount += 1;
      }
    }
    S2.pb(S[l]);
    R2.eb(rmax, rcount);
  }

  int rmax = 0;
  rep(i, 1, sz(S2) - 1) { chmax(rmax, R2[i].fs); }

  int ans = 0;
  rep(i, 1, sz(S2) - 1) {
    if (S2[i] != '#') continue;
    if (R2[i - 1].fs == rmax or R2[i].fs == rmax or R2[i + 1].fs == rmax) {
      ans += R2[i - 1].sd * R2[i + 1].sd;
    }
  }
  cout << ans << '\n';
}
