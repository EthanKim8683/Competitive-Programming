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

  // if X = Y, |S[1]| = X, |S[2]| = |S[3]| = Z
  // is this the only case when it can be all 0's? yes
  //
  // S[1] is Y 0's
  // S[2] is X 0's and Z 1's
  // S[3] is Z 1's and Y 0's

  int X, Y, Z;
  cin >> X >> Y >> Z;

  vc<string> S(3);
  if (X == Y) {
    S[0] = string(X, '0');
    S[1] = S[2] = string(Z, '0');
  } else {
    S[0] = string(Y, '0');
    S[1] = string(X, '0') + string(Z, '1');
    S[2] = string(Z, '1') + string(Y, '0');
  }

  for (auto r : S) {
    cout << sz(r);
    for (auto e : r) {
      cout << ' ' << e;
    }
    cout << '\n';
  }
}
