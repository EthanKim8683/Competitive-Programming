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

const int LOGW = 60;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // read editorial
  //
  // the key observation I was missing was that you want to use smaller X
  // earlier on because more X's are available higher up

  int T;
  cin >> T;

  while (T--) {
    int N, W;
    cin >> N >> W;

    vc<pii> items(N);
    for (auto &[x, y] : items) {
      cin >> x >> y;
    }

    vc<vi> by_x(LOGW);
    for (auto [x, y] : items) {
      by_x[x].pb(y);
    }
    int ans = 0;
    rep(i, 0, LOGW) {
      rep(j, 0, 2) { by_x[i].pb(0); }
      sort(all(by_x[i]));
      reverse(all(by_x[i]));
      int j = 0;
      if ((W >> i & 1) == 1) {
        ans += by_x[i][0];
        j += 1;
      }
      if (i + 1 < LOGW) {
        for (; j + 1 < sz(by_x[i]); j += 2) {
          by_x[i + 1].pb(by_x[i][j] + by_x[i][j + 1]);
        }
      }
    }
    cout << ans << '\n';
  }
}
