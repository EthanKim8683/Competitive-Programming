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

  // get them in pairs; each pair takes 2 dividers -> 2(N/2)=N
  // is this always possible? idk yet
  //
  // could it be 2sat?
  //
  // while it's not in the current set, grow
  //
  // does this work in at most N dividers? yes because we divide at most once
  // per gem type

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(2 * N);
    for (auto &e : A) cin >> e;

    vi ans;
    vc<set<int>> S(2);
    int t = 0;
    rep(i, 0, 2 * N) {
      if (S[t].contains(A[i])) {
        ans.pb(i - 1);
        t ^= 1;
      }
      S[t].insert(A[i]);
    }

    cout << sz(ans) << '\n';
    for (auto e : ans) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}
