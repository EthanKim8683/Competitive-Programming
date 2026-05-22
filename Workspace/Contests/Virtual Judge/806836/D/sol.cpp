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

const int LOGN = 30;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    auto query = [&](int n) -> int {
      cout << n << endl;
      int rv;
      cin >> rv;
      return rv;
    };

    int n1 = 0, n2 = 0;
    rep(i, 0, LOGN) {
      if (i % 2 == 0) {
        n1 |= 1ll << i;
      } else {
        n2 |= 1ll << i;
      }
    }
    int sum1 = query(n1) - (2 * n1), sum2 = query(n2) - (2 * n2), x = 0, y = 0;
    rep(i, 0, LOGN + 1) {
      if (sum1 >> i & 1) {
        if (i % 2 == 0) {
          x |= 1ll << (i - 1);
          y |= 1ll << (i - 1);
        } else {
          x |= 1ll << i;
        }
      }
      if (sum2 >> i & 1) {
        if (i % 2 == 0) {
          x |= 1ll << i;
        } else {
          x |= 1ll << (i - 1);
          y |= 1ll << (i - 1);
        }
      }
    }

    cout << '!' << endl;
    int m;
    cin >> m;

    cout << (m | x) + (m | y) << endl;
  }
}
