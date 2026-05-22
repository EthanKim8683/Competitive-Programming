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

const int MOD = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi X(N + 1);
    rep(i, 1, N + 1) { cin >> X[i]; }

    // give each element a range
    //
    // if X[i] = j, then all (j, i) must end at or before i when is pushed and j
    // must end after
    //
    // range dp?
    //
    // this solves number of ways assuming keeping start
    //
    // less and less
    //
    // set beginning to beginning

    vc dp(N + 2, vi(N + 2, -1));
    auto dfs = [&](auto self, int l, int r) -> int {};
    cout << dfs(dfs, 0, N + 1) << '\n';
  }
}
