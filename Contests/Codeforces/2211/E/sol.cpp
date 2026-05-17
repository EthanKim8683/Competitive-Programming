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

  // break the tree into chains
  //
  // the chains can overlap since removing nodes won't make a chain any less
  // good
  //
  // leaves must have their own good paths so go up greedily
  //
  // if a node can't use any of its descendants' good paths, start a good path
  // here
  //
  // a constraint is that there can be a lot of good paths from descendants
  // maybe small-to-large?
  //
  // maximum number of divisors is ~1e5
  //
  // actually, try just primes

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<unordered_set<int>> good(N);
    vi dp(N, 0);
    for (int i = N - 1; i >= 0; i--) {
      int a, k;
      cin >> a >> k;

      vi C(k);
      for (auto &e : C) {
        cin >> e;
        e--;
      }

      for (auto e : C) {
        for (auto g : good[e]) {
          g = gcd(a, g);
          for (auto e : good[i]) {
            g /= gcd(g, e);
          }
          if (g == 1) continue;
          good[i].insert(g);
        }
        dp[i] += dp[e];
      }
      if (good[i].empty()) {
        if (a != 1) {
          good[i].insert(a);
        }
        dp[i] += 1;
      }
      cout << dp[i] << endl;
    }
  }
}
