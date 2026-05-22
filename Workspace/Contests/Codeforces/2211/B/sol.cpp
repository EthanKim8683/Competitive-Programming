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

const int MAXX = 2e5;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // basically ivt
  //
  // -1 1 -> subarray sum 0
  //
  // reduces to the case with some and none

  vi divisors(MAXX + 1, 0);
  for (int i = 1; i <= MAXX; i++) {
    for (int j = i; j <= MAXX; j += i) {
      divisors[j] += 1;
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int X, Y;
    cin >> X >> Y;

    if (X == Y) {
      cout << "1\n";
      rep(i, 0, X) { cout << "1 "; }
      rep(i, 0, Y) { cout << "-1 "; }
    } else if (X > Y) {
      cout << divisors[X - Y] << '\n';
      rep(i, 0, Y) { cout << "-1 1 "; }
      rep(i, Y, X) { cout << "1 "; }
    } else {
      cout << divisors[Y - X] << '\n';
      rep(i, 0, X) { cout << "1 -1 "; }
      rep(i, X, Y) { cout << "-1 "; }
    }
    cout << '\n';
  }
}
