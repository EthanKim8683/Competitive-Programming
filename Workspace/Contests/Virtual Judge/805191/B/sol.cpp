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

  // never do both 1 and 3

  int T;
  cin >> T;

  while (T--) {
    int X, Y;
    cin >> X >> Y;

    X -= 2 * max(Y, 0ll);
    X -= 4 * max(-Y, 0ll);
    cout << (X >= 0 and X % 3 == 0 ? "YES" : "NO") << '\n';
  }
}
