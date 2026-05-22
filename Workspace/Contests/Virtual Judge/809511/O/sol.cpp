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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // odds can move around between evens
  //
  // split into two groups
  //
  // if there is a smaller or larger even, the inversion can be resolved

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    // worst odd inversion, worst even inversion

    vi mins(2, INF), maxs(2, -INF);
    for (auto e : A) {
      chmin(mins[e % 2], e);
      chmax(maxs[e % 2], e);
    }

    vi maxs2(2, -INF);
    bool ans = true;
    for (auto e : A) {
      if (maxs2[e % 2] > e) {
        ans = ans and (mins[1 - e % 2] < e or maxs[1 - e % 2] > maxs2[e % 2]);
      }
      chmax(maxs2[e % 2], e);
    }
    cout << (ans ? "YES" : "NO") << '\n';
  }
}
