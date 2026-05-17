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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int A, N;
    cin >> A >> N;

    vi D(N);
    for (auto &e : D) cin >> e;

    vi digits;
    if (A == 0) {
      digits.pb(0);
    } else {
      for (int i = A; i != 0; i /= 10) {
        digits.pb(i % 10);
      }
      reverse(all(digits));
    }

    int lt = -10, eq = 0, gt = 10;
    for (auto e : D) {
      if (e == 0) continue;
      chmin(gt, e);
    }
    rep(i, 0, sz(digits)) {
      if (i != 0) {
        chmax(lt, 0);
      }
      lt = lt * 10 + D.back();
      gt = gt * 10 + D[0];
      if (eq != -1) {
        int eq0 = eq;
        eq = -1;
        for (auto e : D) {
          if (e < digits[i]) {
            chmax(lt, eq0 * 10 + e);
          } else if (e == digits[i]) {
            eq = eq0 * 10 + e;
          } else {
            chmin(gt, eq0 * 10 + e);
          }
        }
      }
    }
    int ans = INF;
    chmin(ans, A - lt);
    chmin(ans, gt - A);
    if (eq != -1) {
      chmin(ans, 0);
    }
    cout << ans << '\n';
  }
}
