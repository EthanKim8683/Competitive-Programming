#ifndef L
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/modint.hpp"
using namespace atcoder;

using mint = dynamic_modint<0>;

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
    int N, M, P;
    cin >> N >> M >> P;

    mint::set_mod(P);

    mint ev2 = 0, ev = 0;
    rep(i, 0, N) {
      rep(j, 1, i + 2) {
        mint p = (mint(1) / M).pow(j / 2);
        ev2 += (2 * ev + 1) * p;
        ev += p;
      }
    }
    cout << ev2.val() << '\n';
  }
}
