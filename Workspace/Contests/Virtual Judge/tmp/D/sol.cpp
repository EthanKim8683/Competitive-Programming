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

  int N, Q;
  cin >> N >> Q;

  vi A(N);
  for (auto &e : A) cin >> e;

  vi ps(2 * N + 1);
  ps[0] = 0;
  rep(i, 0, 2 * N) { ps[i + 1] = ps[i] + A[i % N]; }

  int d = 0;
  while (Q--) {
    int t;
    cin >> t;

    if (t == 1) {
      int c;
      cin >> c;

      (d += c) %= N;
    } else {
      int l, r;
      cin >> l >> r;
      l--;

      int n = r - l;
      (l += d) %= N;
      r = l + n;

      cout << ps[r] - ps[l] << '\n';
    }
  }
}
