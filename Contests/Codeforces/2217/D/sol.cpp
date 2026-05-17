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

  // pair diffs
  //
  // in between specials
  //
  // if all have <= m/2, we can pair easy
  //   if m is odd
  //     (m+1)/2 ops, can pick final color
  //   else
  //     m/2 ops, final color is outside
  // else
  //   waste ops until = rest
  //   final m is even
  //   if max was on side
  //     forced
  //   else
  //     can pick final color

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi P(K);
    for (auto &e : P) {
      cin >> e;
      e--;
    }

    vc<bool> is_special(N, false);
    for (auto e : P) {
      is_special[e] = true;
    }

    vi counts;
    int count = 0;
    rep(i, 0, N) {
      if (is_special[i]) {
        counts.pb(count);
        count = 0;
      }
      if (i + 1 < N and A[i + 1] != A[i]) {
        count += 1;
      }
    }
    counts.pb(count);
    int M = accumulate(all(counts), 0ll);

    int d = *max_element(all(counts)), ans;
    if (2 * d > M) {
      ans = d;
      if (counts[0] == d) {
        if ((A.back() == A[P[0]]) != ((d - (M - d)) % 2 == 0)) {
          ans += 1;
        }
      } else if (counts.back() == d) {
        if ((A[0] == A[P[0]]) != ((d - (M - d)) % 2 == 0)) {
          ans += 1;
        }
      }
    } else {
      if (M % 2 == 1) {
        ans = (M + 1) / 2;
      } else {
        ans = M / 2;
        if (A[0] != A[P[0]]) {
          ans += 1;
        }
      }
    }
    cout << ans << '\n';
  }
}
