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
    int N, K, L;
    cin >> N >> K >> L;

    vi A(N);
    for (auto &e : A) cin >> e;
    sort(all(A));
    A.erase(unique(all(A)), A.end());

    vi gaps;
    rep(i, 0, sz(A) - 1) { gaps.pb(A[i + 1] - A[i]); }
    sort(all(gaps));
    reverse(all(gaps));

    int ans = 0, use = 0;
    rep(i, 0, min(sz(gaps) + 1, K + 1)) {
      chmax(ans, use / 2);
      if (i <= K - 1) {
        chmax(ans, use / 2 + max(A[0], L - A.back()) + use / 2 +
                       (K - 1 - i) * (A[0] + L - A.back() + use));
      }
      if (i < sz(gaps)) {
        use += gaps[i];
      }
    }
    cout << ans << '\n';
  }
}
