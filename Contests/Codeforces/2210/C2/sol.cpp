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

const int K = 30;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // lcm of adjacent gcds

  // int l = 1;
  // rep(i, 1, K) {
  //   l = lcm(l, i);
  //   cerr << l << ' ';
  // }
  // cerr << '\n';

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi B(N);
    for (auto &e : B) cin >> e;

    vi G(N);
    rep(i, 0, N) {
      int g = 1;
      if (0 <= i - 1) {
        g = lcm(g, gcd(A[i - 1], A[i]));
      }
      if (i + 1 < N) {
        g = lcm(g, gcd(A[i], A[i + 1]));
      }
      G[i] = g;
    }
  }
}
