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

  // try to make them equal first?
  //
  // try 0 0 -> base
  //
  // if a < b,
  // set d
  // if a < b ^ d,
  //   a = 0
  // else
  //   a = 1

  auto query = [&](int c, int d) -> int {
    cout << "? " << c << ' ' << d << endl;
    int rv;
    cin >> rv;
    return rv;
  };

  int base = query(0, 0);
  if (base == -1) {
    int d = 0;
    for (int i = 30 - 1; i >= 0; i--) {
      if (query(0, d ^ 1 << i) == -1) {
      } else {
      }
    }
  }
}
