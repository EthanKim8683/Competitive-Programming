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
    int P, Q;
    cin >> P >> Q;

    // (P-k)/(Q-k) = 2/3
    // only becomes smaller

    auto check = [&](int x) -> bool {
      // (P-k)/(Q-k) <= 2/3
      // (P-k)*3 <= 2*(Q-k)
      return (P - x) * 3 <= 2 * (Q - x);
    };
    int l = 0, r = min(P, Q - 1);
    while (l < r) {
      int m = l + (r - l) / 2;
      check(m) ? r = m : l = m + 1;
    }
    cout << ((P - l) * 3 == 2 * (Q - l) ? "Bob" : "Alice") << '\n';
  }
}
