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
    int N;
    cin >> N;

    vc<pii> reindeer(N);
    for (auto &[w, p] : reindeer) {
      cin >> w >> p;
    }

    int delta = 0, n = 0;
    vi deltas;
    for (auto [w, p] : reindeer) {
      delta += w;
      n += 1;
      deltas.eb(-w - p);
    }
    sort(all(deltas));

    int ans = 0;
    for (auto e : deltas) {
      delta += e;
      n -= 1;
      if (delta <= 0) {
        chmax(ans, n);
      }
    }
    cout << ans << '\n';
  }
}
