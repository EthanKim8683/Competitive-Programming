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

  // 1: 0
  // 3: 0 1
  // 5: 0 1 2
  // 7: 0 1 2 3
  //
  // if K is odd, it's easy

  int T;
  cin >> T;

  while (T--) {
    int M, K;
    cin >> M >> K;

    vi ans;
    if (K % 2 == 1) {
      ans.resize((K + 1) / 2);
      iota(all(ans), 0);
    } else if (K == 2) {
      if (M % 2 != 0) {
        cout << "No\n";
        continue;
      }
      ans = {0, M / 2};
    } else if (K == 4) {
      if (M % 4 != 0) {
        cout << "No\n";
        continue;
      }
      ans = {0, M / 4, M / 2, 3 * M / 4};
    } else {
      if (M % 2 == 1) {
        if (K % 4 == 0) {
          rep(i, 0, K / 4 + 1) { ans.pb(i); }
          rep(i, 0, K / 4 - 2 + 1) { ans.pb((M + 1) / 2 + i); }
        } else {
          rep(i, 0, (K - 2) / 4 - 1 + 1) { ans.pb(i); }
          rep(i, 0, (K - 2) / 4 + 1) { ans.pb((M + 1) / 2 + i); }
        }
      } else {
        if (K % 4 == 0) {
          rep(i, 0, K / 4 + 1) { ans.pb(i); }
          rep(i, 0, K / 4 - 2 + 1) { ans.pb((M + 2) / 2 + i); }
        } else {
          rep(i, 0, (K - 2) / 4 + 1) { ans.pb(i); }
          rep(i, 0, (K - 2) / 4 + 1) { ans.pb(M / 2 + i); }
        }
      }
    }
    cout << "Yes\n";
    cout << sz(ans) << '\n';
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';

    // cerr << sz(ans) << '\n';
    // for (auto e : ans) {
    //   cerr << e << ' ';
    // }
    // cerr << '\n';

    // set<int> S;
    // for (auto e : ans) {
    //   for (auto e2 : ans) {
    //     S.insert((e + e2) % M);
    //   }
    // }
    // cerr << '\t' << sz(S) << ' ' << K << '\n';
    // assert(sz(S) == K);
  }
}
