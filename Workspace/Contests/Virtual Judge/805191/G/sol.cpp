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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // stack? two stacks?

  int T;
  cin >> T;

  while (T--) {
    int N, M, K;
    cin >> N >> M >> K;

    vc<pii> fountains(K);
    for (auto &[r, c] : fountains) {
      cin >> r >> c;
    }

    map<int, int> by_c;
    by_c[1] = 0;
    for (auto [r, c] : fountains) {
      chmax(by_c[c], r);
    }
    int rmax = -INF;
    for (auto it = by_c.begin(); it != by_c.end();) {
      if (it->sd > rmax) {
        rmax = it->sd;
        it++;
      } else {
        it = by_c.erase(it);
      }
    }

    int ans = N * M, cprev = 0, rprev = 0;
    for (auto [c, r] : by_c) {
      // cerr << '(' << r << ", " << c << ") ";
      ans -= (c - cprev) * rprev;
      cprev = c;
      rprev = r;
    }
    ans -= (M + 1 - cprev) * rprev;
    // cerr << '\n';

    cout << ans << '\n';
    for (auto [r, c] : fountains) {
      cout << (by_c.contains(c) and by_c[c] == r ? '1' : '0') << ' ';
    }
    cout << '\n';
  }
}
