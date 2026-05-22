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

  int T;
  cin >> T;

  while (T--) {
    int X, K;
    cin >> X >> K;

    auto is_prime = [&](int x) -> bool {
      if (x == 1) return false;
      for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
      }
      return true;
    };

    if (K == 1) {
      cout << (is_prime(X) ? "YES" : "NO") << '\n';
    } else {
      if (X == 1) {
        int pow = 1;
        rep(i, 0, K) { pow *= 10; }
        cout << (is_prime((pow - 1) / (10 - 1)) ? "YES" : "NO") << '\n';
      } else {
        cout << "NO\n";
      }
    }
  }
}
