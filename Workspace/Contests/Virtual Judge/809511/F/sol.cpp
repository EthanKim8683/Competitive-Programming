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
    int N, Q;
    cin >> N >> Q;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi X(Q);
    for (auto &e : X) cin >> e;

    // for (auto e : X) {
    //   vi A2 = A;
    //   for (auto &e2 : A2) {
    //     e2 %= e;
    //   }
    //   sort(all(A2));
    //   cout << A2[N / 2] << ' ';
    // }
    // cout << '\n';

    // ps?

    vi ps(2 * N + 2, 0);
    for (auto e : A) {
      ps[e + 1] += 1;
    }
    rep(i, 0, 2 * N + 1) { ps[i + 1] += ps[i]; }

    vi ans(N + 1);
    rep(i, 1, N + 1) {
      auto check = [&](int x) -> bool {
        int count = 0;
        for (int j = 0; j <= N; j += i) {
          count += ps[j + x + 1] - ps[j];
        }
        return count > N / 2;
      };
      int l = 0, r = i - 1;
      while (l < r) {
        int m = l + (r - l) / 2;
        check(m) ? r = m : l = m + 1;
      }
      ans[i] = l;
    }
    for (auto e : X) {
      cout << ans[e] << ' ';
    }
    cout << '\n';
  }
}
