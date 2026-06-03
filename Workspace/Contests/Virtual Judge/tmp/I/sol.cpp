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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, K;
  cin >> N >> K;

  vc C(N, vi(N));
  for (auto &r : C) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  auto eye = [&](int n) -> vc<vi> {
    vc A(n, vi(n, INF));
    rep(i, 0, n) { A[i][i] = 0; }
    return A;
  };

  auto mul = [&](vc<vi> A, vc<vi> B) -> vc<vi> {
    vc C(sz(A), vi(sz(B[0]), INF));
    rep(i, 0, sz(A)) {
      rep(j, 0, sz(B[0])) {
        rep(k, 0, sz(A[0])) { chmin(C[i][j], A[i][k] + B[k][j]); }
      }
    }
    return C;
  };

  auto pow = [&](vc<vi> X, int y) -> vc<vi> {
    auto rv = eye(sz(X));
    for (; y; y >>= 1, X = mul(X, X)) {
      if (y & 1) {
        rv = mul(rv, X);
      }
    }
    return rv;
  };

  auto C2 = pow(C, K);
  rep(i, 0, N) { cout << C2[i][i] << '\n'; }
}
