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

  // if answer is x, then (A[i]+B[j])%M <= x edges have perfect matching
  //
  // A[i] matches with [M-A[i],M-A[i]+x] which can wrap

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi B(N);
    for (auto &e : B) cin >> e;

    vi lefts;
    for (auto e : A) {
      lefts.pb((M - e) % M);
    }
    sort(all(lefts));

    vi B2;
    for (auto e : B) {
      B2.pb(e);
    }
    for (auto e : B) {
      B2.pb(e + M);
    }
    sort(all(B2));

    auto check = [&](int x) -> bool {
      vi ps(N + 1, 0);
      rep(i, 0, N) {
        int l = lower_bound(all(B2), lefts[i]) - B2.begin() - i,
            r = upper_bound(all(B2), lefts[i] + x) - B2.begin() - i;
        for (int j = -N; j <= N; j += N) {
          ps[min(max(l - j, 0ll), N)] += 1;
          ps[min(max(r - j, 0ll), N)] -= 1;
        }
      }
      rep(i, 0, N) { ps[i + 1] += ps[i]; }
      return find(all(ps), N) != ps.end();
    };
    int l = 0, r = M - 1;
    while (l < r) {
      int m = l + (r - l) / 2;
      check(m) ? r = m : l = m + 1;
    }
    cout << l << '\n';
  }
}
