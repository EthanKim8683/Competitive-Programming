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
    int N, K;
    cin >> N >> K;
    K--;

    vi indices;
    rep(i, 0, __lg(N) + 1) {
      if ((N >> i & 1) == 1) continue;
      indices.pb(i);
    }
    if (K >= (1 << sz(indices))) {
      cout << "-1\n";
      continue;
    }

    int ans = N;
    rep(i, 0, sz(indices)) { ans |= (K >> i & 1) << indices[i]; }
    cout << ans << '\n';
  }
}
