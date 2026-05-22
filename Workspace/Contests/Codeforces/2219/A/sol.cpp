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

    pii ans = {-1, -1};
    for (int i = 1; 2 * i * i + 2 * i <= 2 * Q + P; i++) {
      int j = (2 * Q + P) - (2 * i * i + 2 * i);
      if (j % (2 * i + 1) != 0) continue;
      int k = j / (2 * i + 1);
      if (k > P) continue;
      ans = {i, i + k};
    }
    if (ans == pii{-1, -1}) {
      cout << "-1\n";
      continue;
    }
    auto [n, m] = ans;
    cout << n << ' ' << m << '\n';
  }
}
