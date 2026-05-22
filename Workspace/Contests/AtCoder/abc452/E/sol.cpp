#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/modint.hpp"
using namespace atcoder;

using mint = modint998244353;

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

  //

  int N, M;
  cin >> N >> M;

  vi A(N + 1);
  rep(i, 1, N + 1) { cin >> A[i]; }

  vi B(M + 1);
  rep(i, 1, M + 1) { cin >> B[i]; }

  vc<mint> ps(N + 2);
  ps[0] = 0;
  rep(i, 0, N + 1) { ps[i + 1] = ps[i] + A[i]; }

  mint base = 0;
  rep(i, 0, N + 1) { base += A[i] * i; }

  mint ans = 0;
  rep(i, 1, M + 1) {
    mint sum = base;
    for (int j = 0; j < N + 1; j += i) {
      sum -= (ps[min(j + i, N + 1)] - ps[j]) * j;
    }
    ans += sum * B[i];
  }
  cout << ans.val() << '\n';
}
