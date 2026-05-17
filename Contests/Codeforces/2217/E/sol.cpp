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

  // go back to front
  //
  // of the ones with j>i and P[j]>P[i], D[i] have Q[j]>Q[i]
  //
  // insert Q[i]

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi P(N);
    for (auto &e : P) {
      cin >> e;
      e--;
    }

    vi D(N);
    for (auto &e : D) cin >> e;

    vi ans(N);
    bool ok = true;
    for (int i = N - 1; i >= 0; i--) {
      vi Q;
      rep(j, i + 1, N) {
        if (!(P[j] > P[i])) continue;
        Q.pb(ans[j]);
      }
      sort(all(Q));
      if (D[i] > sz(Q)) {
        ok = false;
        break;
      }
      if (D[i] == 0) {
        ans[i] = N - 1 - i;
      } else {
        ans[i] = Q.end()[-D[i]];
      }
      rep(j, i + 1, N) {
        if (ans[j] < ans[i]) continue;
        ans[j] += 1;
      }
    }
    if (!ok) {
      cout << "-1\n";
      continue;
    }
    for (auto e : ans) {
      cout << e + 1 << ' ';
    }
    cout << '\n';

    // for (auto e : D) {
    //   cerr << e << ' ';
    // }
    // cerr << '\n';
    // rep(i, 0, N) {
    //   int d = 0;
    //   rep(j, i + 1, N) {
    //     if (P[j] > P[i] and ans[j] > ans[i]) {
    //       d += 1;
    //     }
    //   }
    //   cerr << d << ' ';
    // }
    // cerr << '\n';
  }
}
