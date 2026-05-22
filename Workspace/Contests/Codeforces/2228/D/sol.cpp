#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

// #define int long long
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

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<pii> points(N);
    for (auto &[x, y] : points) {
      cin >> x >> y;
      x--, y--;
    }

    vc<bool> seen1(N, false), seen2(N, false);
    for (auto [x, y] : points) {
      seen1[x] = true;
      seen2[y] = true;
    }
    vi cc1(N), cc2(N);
    int k1 = 0, k2 = 0;
    rep(i, 0, N) {
      if (seen1[i]) {
        cc1[i] = k1;
        k1++;
      }
      if (seen2[i]) {
        cc2[i] = k2;
        k2++;
      }
    }
    for (auto &[x, y] : points) {
      x = cc1[x];
      y = cc2[y];
    }

    vi pmins(k1, INF), pmaxs(k1, -INF), smins(k1, INF), smaxs(k1, -INF);
    for (auto [x, y] : points) {
      chmin(pmins[x], y);
      chmax(pmaxs[x], y);
      chmin(smins[x], y);
      chmax(smaxs[x], y);
    }
    rep(i, 0, k1 - 1) {
      chmin(pmins[i + 1], pmins[i]);
      chmax(pmaxs[i + 1], pmaxs[i]);
    }
    for (int i = k1 - 1; i >= 1; i--) {
      chmin(smins[i - 1], smins[i]);
      chmax(smaxs[i - 1], smaxs[i]);
    }

    long long ans = 0;
    rep(i, 0, k1 - 1) {
      ans += max(min(pmaxs[i], smaxs[i + 1]) - max(pmins[i], smins[i + 1]), 0);
    }
    cout << ans << '\n';
  }
}
