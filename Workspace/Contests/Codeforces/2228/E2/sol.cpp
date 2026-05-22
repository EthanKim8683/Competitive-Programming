#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/modint.hpp"
#include "atcoder/segtree.hpp"
using namespace atcoder;

using mint = modint998244353;

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

  int T;
  cin >> T;

  while (T--) {
    int N, Q;
    cin >> N >> Q;

    vi A(N);
    for (auto &e : A) cin >> e;

    while (Q--) {
      int t;
      cin >> t;

      if (t == 1) {
        int p, v;
        cin >> p >> v;
        p--;
      } else {
        int l, r, m;
        cin >> l >> r >> m;
        l--;
      }
    }
  }
}
