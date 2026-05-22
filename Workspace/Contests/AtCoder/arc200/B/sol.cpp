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

const int MAXA = 17;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  vi pows(MAXA + 1);
  pows[0] = 1;
  rep(i, 1, MAXA + 1) { pows[i] = pows[i - 1] * 10; }

  int T;
  cin >> T;

  while (T--) {
    int A1, A2, A3;
    cin >> A1 >> A2 >> A3;

    if (A3 < max(A1, A2)) {
      cout << "No\n";
      continue;
    }

    if (A3 > A1 + A2) {
      cout << "No\n";
      continue;
    }

    int x1, x2;
    if (A3 == max(A1, A2)) {
      x1 = pows[A1 - 1];
      x2 = pows[A2 - 1];
    } else if (A3 == A1 + A2) {
      x1 = pows[A1] - 1;
      x2 = pows[A2] - 1;
      if (gcd(x1, x2) != 1) {
        x2 -= 1;
      }
    } else {
      x1 = pows[A1 - 1];
      x2 = (pows[A3 - A1 + 1] - 1) * pows[A2 - (A3 - A1 + 1)];
    }
    cout << "Yes\n" << x1 << ' ' << x2 << '\n';

    // cerr << x1 << ' ' << x2 << ' ' << lcm(x1, x2) << '\n';
    // assert(sz(to_string(x1)) == A1);
    // assert(sz(to_string(x2)) == A2);
    // assert(sz(to_string(lcm(x1, x2))) == A3);
  }
}
