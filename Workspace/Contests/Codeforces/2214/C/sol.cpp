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

  // string S = "RXOEARDMTINHUSERMEDESIANT";

  // int K = 20260401;

  // rep(i, 0, sz(S)) {
  //   cout << (K >> (sz(S) - 1 - i) & 1) << ' ' << S[i] << '\n';
  // }

  // READTHEREST
  // XORMINUSMEDIAN

  int T;
  cin >> T;

  while (T--) {
    vi A(3);
    for (auto &e : A) cin >> e;

    int x = 0;
    for (auto e : A) {
      x ^= e;
    }
    sort(all(A));
    cout << x - A[1] << '\n';
  }
}
