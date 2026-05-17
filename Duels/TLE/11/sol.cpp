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
    int N, S1, S2;
    cin >> N >> S1 >> S2;

    vi R(N);
    for (auto &e : R) cin >> e;

    vi order(N);
    iota(all(order), 0);
    sort(all(order), [&](int a, int b) -> bool { return R[a] > R[b]; });

    int sum1 = S1, sum2 = S2;
    vi ans1, ans2;
    for (auto e : order) {
      if (sum1 < sum2) {
        ans1.pb(e);
        sum1 += S1;
      } else {
        ans2.pb(e);
        sum2 += S2;
      }
    }
    cout << sz(ans1);
    for (auto e : ans1) {
      cout << ' ' << e + 1;
    }
    cout << '\n';
    cout << sz(ans2);
    for (auto e : ans2) {
      cout << ' ' << e + 1;
    }
    cout << '\n';
  }
}
