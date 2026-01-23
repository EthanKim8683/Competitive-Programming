#pragma GCC optimize("Ofast,unroll-loops")
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

const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vc<pii> ranges(M);
    for (auto &[l, r] : ranges) {
      cin >> l >> r;
    }

    vi left(N, 0);
    for (auto [l, r] : ranges) {
      chmax(left[r - 1], l);
    }

    vi ps(N + 1, 0);
    ps[1] = 2;
    int l = 0;
    rep(i, 1, N) {
      ps[i + 1] = (ps[i] + ps[i] + MOD - ps[l]) % MOD;
      chmax(l, left[i]);
    }
    cout << (ps[N] + MOD - ps[l]) % MOD << '\n';
  }
}
