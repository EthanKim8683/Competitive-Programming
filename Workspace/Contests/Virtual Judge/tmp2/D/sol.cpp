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

  // dsu??

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<pii> segments(N);
    for (auto &[l, r] : segments) {
      cin >> l >> r;
      l--;
    }

    vi order(N);
    iota(all(order), 0);
    sort(all(order),
         [&](int a, int b) -> bool { return segments[a] < segments[b]; });

    dsu d(N);
    int rmax = 0;
    rep(i, 0, N) {
      auto [l, r] = segments[order[i]];
      if (rmax > l) {
        d.merge(order[i], order[i - 1]);
      }
      chmax(rmax, r);
    }

    set<int> leaders;
    rep(i, 0, N) { leaders.insert(d.leader(i)); }
    if (sz(leaders) < 2) {
      cout << "-1\n";
      continue;
    }

    int diff = *leaders.begin();
    rep(i, 0, N) { cout << (d.leader(i) == diff ? 2 : 1) << ' '; }
    cout << '\n';
  }
}
